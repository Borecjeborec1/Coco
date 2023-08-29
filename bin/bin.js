#!/usr/bin/env node

const CocoCompiler = require('../index.js');
const process = require('process');

async function main(args) {
  const options = parseArguments(args);
  const coco = new CocoCompiler(options.inputFile, options.outputFile, options.cppFile)
  if (options.version) {
    coco.printVersion();
  } else if (options.inputFile) {
    console.time("Building cpp")
    await coco.buildCpp()
    console.timeEnd("Building cpp")
    console.time("Compiling cpp")
    await coco.compile()
    console.timeEnd("Compiling cpp")
    console.time("Running exe")
    await coco.run(coco)
    console.timeEnd("Running exe")
  } else {
    coco.printUsage();
  }
}

function parseArguments(args) {
  const options = {
    version: false,
    inputFile: '',
    outputFile: '',
    cppFile: ''
  };

  for (let i = 0; i < args.length; i++) {
    const arg = args[i];

    switch (arg) {
      case '-v':
      case '--version':
        options.version = true;
        break;

      case '-o':
      case '--output':
        options.outputFile = args[i + 1] || '';
        i++;
        break;

      case '--cpp':
        options.cppFile = args[i + 1] || '';
        i++;
        break;

      default:
        options.inputFile = arg;
        break;
    }
  }

  return options;
}

main(process.argv.slice(2));
