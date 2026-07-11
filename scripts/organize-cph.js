const fs = require('fs');
const path = require('path');
const axios = require('axios');
const cheerio = require('cheerio');
const { execSync } = require('child_process');

const ROOT_DIR = path.join(__dirname, '..');
const TEMPLATE_README = path.join(ROOT_DIR, 'templates', 'README_TEMPLATE.md');

function cleanTestCase(html) {
    if (!html) return "";
    return html.replace(/<br\s*\/?>/gi, '\n')
               .replace(/<div.*?>/gi, '')
               .replace(/<\/div>/gi, '\n')
               .replace(/<[^>]*>?/gm, '')
               .trim();
}

// ---- DOM-based parser ----
function parseSection(html) {
    if (!html) return "";
    
    const $ = cheerio.load(html, { decodeEntities: true });
    
    function walk(node) {
        if (node.type === 'text') {
            return node.data.replace(/&nbsp;/g, ' ').replace(/\s+/g, ' ');
        }
        
        if (node.type === 'tag') {
            const $el = $(node);
            const tagName = node.name;
            
            // ---- Inline math ----
            if (tagName === 'span' && $el.hasClass('tex-span')) {
                let content = walkChildren(node);
                content = content.trim();
                // Strip any surrounding $ (single or multiple)
                content = content.replace(/^\$+/, '').replace(/\$+$/, '');
                content = content.trim();
                
                // Check for footnote markers like ^{\dagger}, ^{\text{∗}}
                if (/^\\?\{\s*(?:\\text)?\s*([∗†*])\s*\}$/.test(content)) {
                    const symbol = content.match(/([∗†*])/)[1];
                    return symbol === '†' ? '†' : '*';
                }
                if (['∗', '†', '*'].includes(content)) return content;
                
                return `$${content}$`;
            }
            
            // ---- Display math ----
            if (tagName === 'div' && $el.hasClass('tex')) {
                let content = walkChildren(node);
                content = content.trim();
                content = content.replace(/^\$+/, '').replace(/\$+$/, '');
                content = content.trim();
                return `\n$$${content}$$\n`;
            }
            
            // ---- Section title ----
            if (tagName === 'div' && $el.hasClass('section-title')) {
                return `\n### ${walkChildren(node).trim()}\n`;
            }
            
            // ---- Bold ----
            if (tagName === 'span' && $el.hasClass('tex-font-style-bf')) {
                return `**${walkChildren(node).trim()}**`;
            }
            
            // ---- Italic ----
            if (tagName === 'span' && $el.hasClass('tex-font-style-it')) {
                return `*${walkChildren(node).trim()}*`;
            }
            
            // ---- Superscript (footnotes) ----
            if (tagName === 'sup') {
                const content = walkChildren(node).trim();
                if (['∗', '*', '\\text{∗}', '\\dagger', '\\text{†}', '†'].includes(content)) {
                    return content === '†' || content === '\\text{†}' || content === '\\dagger' ? '†' : '*';
                }
                return `^(${content})`;
            }
            
            // ---- Paragraph ----
            if (tagName === 'p') {
                const content = walkChildren(node).trim();
                return content ? `\n${content}\n` : '';
            }
            
            // ---- Line break ----
            if (tagName === 'br') {
                return '\n';
            }
            
            // ---- List item ----
            if (tagName === 'li') {
                return `- ${walkChildren(node).trim()}\n`;
            }
            
            // ---- Other block elements ----
            if (['div', 'section', 'article', 'span'].includes(tagName)) {
                return walkChildren(node);
            }
            
            return walkChildren(node);
        }
        return '';
    }
    
    function walkChildren(node) {
        let result = '';
        if (node.children) {
            for (const child of node.children) {
                result += walk(child);
            }
        }
        return result;
    }
    
    const body = $('body')[0];
    let output = walk(body);
    
    output = output.replace(/\n{3,}/g, '\n\n');
    output = output.replace(/ \n/g, '\n');
    output = output.replace(/\n /g, '\n');
    
    return output.trim();
}

// ---- FETCH (unchanged, robust) ----
async function fetchHtml(url) {
    const userAgent = 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36';
    const headers = {
        'User-Agent': userAgent,
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
        'Accept-Language': 'en-US,en;q=0.5',
        'Accept-Encoding': 'gzip, deflate, br',
        'Connection': 'keep-alive',
        'Upgrade-Insecure-Requests': '1',
        'Sec-Fetch-Dest': 'document',
        'Sec-Fetch-Mode': 'navigate',
        'Sec-Fetch-Site': 'none',
        'Sec-Fetch-User': '?1',
        'Cache-Control': 'max-age=0'
    };

    try {
        const response = await axios.get(url, { headers, timeout: 15000 });
        const html = response.data;
        if (!html.includes('Just a moment...') && !html.includes('Temporarily unavailable')) {
            return html;
        }
    } catch (e) {
        console.log(`[!] Axios failed: ${e.message}`);
    }

    try {
        const cmd = `curl -sL -k -H "User-Agent: ${userAgent}" -H "Accept: text/html" -H "Accept-Language: en-US" -H "Connection: keep-alive" -H "Upgrade-Insecure-Requests: 1" "${url}"`;
        const html = execSync(cmd, { maxBuffer: 10 * 1024 * 1024 }).toString();
        if (!html.includes('Just a moment...') && !html.includes('Temporarily unavailable')) {
            return html;
        }
    } catch (e) {}

    throw new Error('All fetch methods failed (Cloudflare/403)');
}

// ---- GET METADATA ----
async function getProblemMetadata(contestId, problemLetter) {
    try {
        const response = await axios.get(
            `https://codeforces.com/api/contest.standings?contestId=${contestId}&from=1&count=1`
        );
        if (response.data.status === 'OK') {
            const problems = response.data.result.problems;
            const problem = problems.find(p => p.index === problemLetter.toUpperCase());
            if (problem) {
                return {
                    tags: problem.tags || [],
                    rating: problem.rating ? problem.rating.toString() : null
                };
            }
        }
    } catch (e) {}
    return null;
}

// ---- FIND LATEST .PROB ----
function findLatestProbFile() {
    const cphDir = path.join(ROOT_DIR, '.cph');
    if (!fs.existsSync(cphDir)) return null;
    const files = fs.readdirSync(cphDir).filter(f => f.endsWith('.prob'));
    if (files.length === 0) return null;
    let latest = null, latestTime = 0;
    for (const file of files) {
        const stat = fs.statSync(path.join(cphDir, file));
        if (stat.mtimeMs > latestTime) {
            latestTime = stat.mtimeMs;
            latest = file;
        }
    }
    return latest ? path.join(cphDir, latest) : null;
}

// ---- MAIN ----
async function organize() {
    console.log('🔍 Looking for recently fetched problem...');

    const probFilePath = findLatestProbFile();
    if (!probFilePath) {
        console.log('❌ No .prob file found. Fetch a problem first with Competitive Companion.');
        return;
    }

    console.log(`📄 Found: ${path.basename(probFilePath)}`);

    const probData = JSON.parse(fs.readFileSync(probFilePath, 'utf8'));
    const name = probData.name;
    const url = probData.url;
    const tests = probData.tests || [];
    const timeLimitMs = probData.timeLimit || 1500;
    const memoryLimitMb = probData.memoryLimit || 256;

    const urlMatch = url.match(/\/problem\/(\d+)\/([A-Z])/);
    if (!urlMatch) {
        console.log('❌ Could not parse contest/problem from URL');
        return;
    }
    const contestId = urlMatch[1];
    const problemLetter = urlMatch[2];
    console.log(`📊 Contest: ${contestId}, Problem: ${problemLetter}`);

    console.log(`🌐 Fetching page: ${url}`);
    let htmlData;
    try {
        htmlData = await fetchHtml(url);
    } catch (error) {
        console.error(`❌ Failed to fetch: ${error.message}`);
        return;
    }

    const $ = cheerio.load(htmlData);

    // ---- Get rating and tags ----
    let tags = [];
    let rating = 'Unrated';

    const meta = await getProblemMetadata(contestId, problemLetter);
    if (meta && meta.rating) {
        tags = meta.tags;
        rating = meta.rating;
        console.log(`⭐ Rating from API: ${rating}`);
    } else {
        $('.tag-box').each((i, el) => {
            const text = $(el).text().trim();
            if (text.startsWith('*')) {
                rating = text.substring(1);
            } else if (!isNaN(text) && text !== '') {
                rating = text;
            } else {
                tags.push(text);
            }
        });
        if (rating === 'Unrated') {
            const numericTag = tags.find(t => !isNaN(t) && t !== '');
            if (numericTag) {
                rating = numericTag;
                tags = tags.filter(t => t !== numericTag);
            }
        }
        console.log(`⭐ Rating from DOM: ${rating}`);
    }

    console.log(`🏷️  Tags: ${tags.join(', ') || 'None'}`);

    // ---- Build statement ----
    const mainText = parseSection($('.problem-statement > div:not([class])').first().html());
    const inputSpec = parseSection($('.problem-statement .input-specification').html());
    const outputSpec = parseSection($('.problem-statement .output-specification').html());
    const noteSpec = parseSection($('.problem-statement .note').html());

    // Extract sample tests
    const inputs = [], outputs = [];
    $('.sample-test .input pre').each((i, el) => { inputs.push(cleanTestCase($(el).html())); });
    $('.sample-test .output pre').each((i, el) => { outputs.push(cleanTestCase($(el).html())); });

    let examplesSpec = "### Examples\n\n";
    inputs.forEach((input, index) => {
        examplesSpec += `**Input**\n\`\`\`text\n${input}\n\`\`\`\n\n**Output**\n\`\`\`text\n${outputs[index]}\n\`\`\`\n\n`;
    });

    let fullStatement = `${mainText}\n\n${inputSpec}\n\n${outputSpec}\n\n${examplesSpec}`;
    if ($('.problem-statement .note').length > 0) fullStatement += `${noteSpec}\n\n`;

    // ---- POST-PROCESS: FIX DOUBLE DOLLARS AND FOOTNOTES ----
    fullStatement = fullStatement.replace(/\$\$([^\n]+?)\$\$/g, (match, content) => {
        // If content is a footnote marker
        if (/^\\?\{\s*(?:\\text)?\s*([∗†*])\s*\}$/.test(content.trim())) {
            const symbol = content.trim().match(/([∗†*])/)[1];
            return symbol === '†' ? '†' : '*';
        }
        // If content contains superscript footnote patterns
        if (content.includes('^{\\dagger}') || content.includes('^{\\text{†}}')) {
            return '†';
        }
        if (content.includes('^{*}') || content.includes('^{\\text{∗}}')) {
            return '*';
        }
        // Otherwise convert double to single $ (inline)
        return `$${content}$`;
    });

    // Also handle standalone double-dollar footnotes that might have been converted to display math
    fullStatement = fullStatement.replace(/\$\$\\?\{\s*(?:\\text)?\s*([∗†*])\s*\}\$\$/g, (match, symbol) => {
        return symbol === '†' ? '†' : '*';
    });

    // ---- Create folder ----
    const safeTitle = name.replace(/[^a-zA-Z0-9]/g, '_').replace(/_+/g, '_');
    const folderName = `${contestId}${problemLetter}_${safeTitle}`;
    const ratingFolder = path.join(ROOT_DIR, rating);
    if (!fs.existsSync(ratingFolder)) {
        fs.mkdirSync(ratingFolder, { recursive: true });
        console.log(`📁 Created rating folder: ${rating}/`);
    }
    const problemFolder = path.join(ratingFolder, folderName);
    if (!fs.existsSync(problemFolder)) {
        fs.mkdirSync(problemFolder, { recursive: true });
        console.log(`📁 Created problem folder: ${rating}/${folderName}`);
    }

    // ---- Move source file ----
    const sourceFile = probData.srcPath;
    if (sourceFile && fs.existsSync(sourceFile)) {
        const fileName = path.basename(sourceFile);
        const destFile = path.join(problemFolder, fileName);
        fs.renameSync(sourceFile, destFile);
        console.log(`📄 Moved: ${fileName} → ${rating}/${folderName}/`);
    }

    // ---- Write README ----
    let readmeContent = fs.readFileSync(TEMPLATE_README, 'utf-8');
    const timeLimitSeconds = (timeLimitMs / 1000).toFixed(1) + ' seconds';
    readmeContent = readmeContent
        .replace('{{TITLE}}', `${contestId}${problemLetter} - ${name}`)
        .replace('{{URL}}', url)
        .replace('{{RATING}}', rating)
        .replace('{{TAGS}}', tags.length ? tags.join(', ') : 'None')
        .replace('{{TIME_LIMIT}}', timeLimitSeconds)
        .replace('{{MEMORY_LIMIT}}', memoryLimitMb + ' megabytes')
        .replace('{{STATEMENT}}', fullStatement.trim());

    fs.writeFileSync(path.join(problemFolder, 'README.md'), readmeContent);
    console.log('📝 Created: README.md');

    // ---- Write samples ----
    tests.forEach((test, idx) => {
        fs.writeFileSync(path.join(problemFolder, `in${idx + 1}.txt`), test.input);
        fs.writeFileSync(path.join(problemFolder, `out${idx + 1}.txt`), test.output);
    });
    console.log(`📝 Created: ${tests.length} sample test(s)`);

    // ---- Copy template ----
    const templateCpp = path.join(ROOT_DIR, 'templates', 'solution.cpp');
    const solutionCpp = path.join(problemFolder, 'solution.cpp');
    if (fs.existsSync(templateCpp) && !fs.existsSync(solutionCpp)) {
        fs.copyFileSync(templateCpp, solutionCpp);
        console.log('📄 Copied: solution.cpp');
    }

    console.log(`\n✅ SUCCESS! Problem organized to: ${rating}/${folderName}`);
    console.log(`   cd ${rating}/${folderName}`);
}

organize().catch(console.error);