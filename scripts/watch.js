const chokidar = require('chokidar');
const { exec } = require('child_process');
const path = require('path');

const CPH_DIR = path.join(__dirname, '..', '.cph');
const ORGANIZER_SCRIPT = path.join(__dirname, 'organize-cph.js');

console.log(`👀 Watching ${CPH_DIR} for new .prob files...`);

let processing = false;

function scheduleOrganize(filePath) {
    if (processing) return;
    processing = true;
    console.log(`📄 New .prob file detected: ${path.basename(filePath)}`);
    console.log('⏳ Waiting 2 seconds for file to be written...');

    setTimeout(() => {
        console.log('🔄 Running organizer...');
        exec(`node "${ORGANIZER_SCRIPT}"`, { cwd: path.join(__dirname, '..') }, (error, stdout, stderr) => {
            if (error) {
                console.error(`❌ Organizer error: ${error.message}`);
            } else {
                console.log(stdout);
                if (stderr) console.error(stderr);
            }
            processing = false;
        });
    }, 2000);
}

const watcher = chokidar.watch(CPH_DIR, {
    persistent: true,
    ignoreInitial: true,
    awaitWriteFinish: true,
});

watcher.on('add', (filePath) => {
    if (filePath.endsWith('.prob')) {
        const fs = require('fs');
        try {
            const stats = fs.statSync(filePath);
            if (stats.size > 0) {
                scheduleOrganize(filePath);
            }
        } catch (err) {}
    }
});

console.log('✅ Watcher is running with chokidar. Press Ctrl+C to stop.');