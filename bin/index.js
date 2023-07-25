#!/usr/bin/env node

const coco = require('../index.js');
const process = require('process');

async function main(args) {
  if (!args.length) {
    console.log('Usage:');
    console.log('-v, --version: Print the version');
    console.log('-o, --output <file>: Compile with the specified output file');
    console.log('Example:');
    console.log('mypackage inputFile.js');
    console.log('mypackage -v');
    console.log('mypackage inputFile.js -o outputFile.cc');
    return
  }

  if (args.includes('-v') || args.includes('--version')) {
    const packageJson = require('../package.json');
    console.log(`Version: ${packageJson.version}`);
    return
  }

  const inputFile = args[0];
  await coco.init(inputFile, args[1]);
  await coco.build();
  await coco.compile();
  await coco.run();

}

main(process.argv.slice(2)) 