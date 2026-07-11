const puppeteer = require('puppeteer');
const cheerio = require('cheerio');
const fs = require('fs');
const path = require('path');
const axios = require('axios');

const ROOT_DIR = path.join(__dirname, '..');
const TEMPLATE_README = path.join(ROOT_DIR, 'templates', 'README_TEMPLATE.md');
const TEMPLATE_CPP = path.join(ROOT_DIR, 'templates', 'solution.cpp');

// ---- Your original helpers (keep as-is) ----
function cleanTestCase(html) {
    if (!html) return "";
    return html.replace(/<br\s*\/?>/gi, '\n')
               .replace(/<div.*?>/gi, '')
               .replace(/<\/div>/gi, '\n')
               .replace(/<[^>]*>?/gm, '')
               .trim();
}

function parseSection(html) {
    if (!html) return "";
    return html.replace(/<div class="section-title">(.*?)<\/div>/g, '### $1\n')
               .replace(/<br\s*\/?>/gi, '\n')
               .replace(/<p>/g, '')
               .replace(/<\/p>/g, '\n\n')
               .replace(/<span class="tex-font-style-bf">(.*?)<\/span>/g, '**$1**')
               .replace(/<span class="tex-font-style-it">(.*?)<\/span>/g, '*$1*')
               .replace(/<[^>]*>?/gm, '')
               .trim();
}

// ---- Fetch with Puppeteer (bypasses Cloudflare) ----
async function fetchHtmlWithPuppeteer(url) {
    const browser = await puppeteer.launch({ headless: true });
    try {
        const page = await browser.newPage();
        await page.setUserAgent('Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36');
        await page.goto(url, { waitUntil: 'networkidle2', timeout: 30000 });
        const html = await page.content();
        return html;
    } finally {
        await browser.close();
    }
}

// ---- Main ----
async function fetchProblemData(contestId, problemLetter, mode = 'practice') {
    let title = "Unknown", tags = [], rating = "Unrated";
    let apiSuccess = false;

    // 1. Try API for metadata (rating, tags, title)
    try {
        console.log(`[1/6] Querying Codeforces API...`);
        const apiUrl = `https://codeforces.com/api/contest.standings?contestId=${contestId}&from=1&count=1`;
        const apiResponse = await axios.get(apiUrl);
        if (apiResponse.data.status === 'OK') {
            const problems = apiResponse.data.result.problems;
            const problemMeta = problems.find(p => p.index === problemLetter.toUpperCase());
            if (problemMeta) {
                title = problemMeta.name;
                tags = problemMeta.tags || [];
                rating = problemMeta.rating ? problemMeta.rating.toString() : "Unrated";
                apiSuccess = true;
                console.log(`[2/6] API success: "${title}" (Rating: ${rating})`);
            }
        }
    } catch (error) {
        console.log(`[2/6] API restricted. Falling back to scrape...`);
    }

    // 2. Fetch problem page using Puppeteer (works despite Cloudflare)
    const targetUrl = mode === 'contest'
        ? `https://codeforces.com/contest/${contestId}/problem/${problemLetter}`
        : `https://codeforces.com/problemset/problem/${contestId}/${problemLetter}`;

    console.log(`[3/6] Fetching with Puppeteer: ${targetUrl}`);
    let htmlData;
    try {
        htmlData = await fetchHtmlWithPuppeteer(targetUrl);
    } catch (error) {
        console.error(`❌ Puppeteer fetch failed: ${error.message}`);
        process.exit(1);
    }

    const $ = cheerio.load(htmlData);

    // 3. Extract metadata from DOM if API failed
    if (!apiSuccess) {
        const rawTitle = $('.problem-statement .header .title').text().trim();
        title = rawTitle.substring(rawTitle.indexOf('.') + 1).trim() || "Unknown";
        $('.tag-box').each((i, el) => {
            const tagText = $(el).text().trim();
            // Check if tagText is numeric (rating)
            if (!isNaN(tagText) && tagText !== '') {
                rating = tagText;           // it's the rating
            } else {
                tags.push(tagText);         // it's a problem tag
            }
        });
        console.log(`[2/6] Scraped rating: ${rating}`);
    }

    // 4. Time / memory
    const timeLimit = $('.problem-statement .header .time-limit').text().replace('time limit per test', '').trim();
    const memoryLimit = $('.problem-statement .header .memory-limit').text().replace('memory limit per test', '').trim();

    // 5. Build statement using your original parseSection
    const mainText = parseSection($('.problem-statement > div:not([class])').first().html());
    const inputSpec = parseSection($('.problem-statement .input-specification').html());
    const outputSpec = parseSection($('.problem-statement .output-specification').html());
    const noteSpec = parseSection($('.problem-statement .note').html());

    const inputs = [], outputs = [];
    $('.sample-test .input pre').each((i, el) => { inputs.push(cleanTestCase($(el).html())); });
    $('.sample-test .output pre').each((i, el) => { outputs.push(cleanTestCase($(el).html())); });

    let examplesSpec = "### Examples\n\n";
    inputs.forEach((input, index) => {
        examplesSpec += `**Input**\n\`\`\`text\n${input}\n\`\`\`\n\n**Output**\n\`\`\`text\n${outputs[index]}\n\`\`\`\n\n`;
    });

    let fullStatement = `${mainText}\n\n${inputSpec}\n\n${outputSpec}\n\n${examplesSpec}`;
    if ($('.problem-statement .note').length > 0) fullStatement += `${noteSpec}\n\n`;

    // 6. Create folder based on rating
    const safeTitle = title.replace(/[^a-zA-Z0-9]/g, '_').replace(/_+/g, '_');
    const folderName = `${contestId}${problemLetter}_${safeTitle}`;
    const targetRatingFolder = path.join(ROOT_DIR, rating);
    // If rating is "Unrated" or folder doesn't exist, fall back to root
    const finalFolderPath = (rating !== 'Unrated' && fs.existsSync(targetRatingFolder))
        ? path.join(targetRatingFolder, folderName)
        : path.join(ROOT_DIR, folderName);

    if (!fs.existsSync(finalFolderPath)) {
        fs.mkdirSync(finalFolderPath, { recursive: true });
        console.log(`[4/6] Created folder: ${finalFolderPath}`);
    }

    // 7. Write README
    let readmeContent = fs.readFileSync(TEMPLATE_README, 'utf-8');
    readmeContent = readmeContent
        .replace('{{TITLE}}', `${contestId}${problemLetter} - ${title}`)
        .replace('{{URL}}', targetUrl)
        .replace('{{RATING}}', rating)
        .replace('{{TAGS}}', tags.length ? tags.join(', ') : 'None')
        .replace('{{TIME_LIMIT}}', timeLimit)
        .replace('{{MEMORY_LIMIT}}', memoryLimit)
        .replace('{{STATEMENT}}', fullStatement.trim());

    fs.writeFileSync(path.join(finalFolderPath, 'README.md'), readmeContent);
    console.log('[5/6] README.md written');

    // 8. Sample files
    inputs.forEach((input, idx) => {
        fs.writeFileSync(path.join(finalFolderPath, `in${idx + 1}.txt`), input + '\n');
    });
    outputs.forEach((output, idx) => {
        fs.writeFileSync(path.join(finalFolderPath, `out${idx + 1}.txt`), output + '\n');
    });
    console.log(`[5/6] ${inputs.length} sample test(s) saved.`);

    // 9. Copy solution template
    fs.copyFileSync(TEMPLATE_CPP, path.join(finalFolderPath, 'solution.cpp'));
    console.log('[6/6] solution.cpp copied');

    console.log(`✅ Success! Problem saved to: ${finalFolderPath}`);
    console.log(`   cd ${path.relative(ROOT_DIR, finalFolderPath)}`);
}

// ---- CLI ----
const args = process.argv.slice(2);
if (args.length < 2) {
    console.error('Usage: node cf-init.js <contestId> <problemLetter> [mode]');
    console.error('  mode: "contest" or "practice" (default: practice)');
    process.exit(1);
}
fetchProblemData(args[0], args[1], args[2] || 'practice').catch(console.error);