#!/usr/bin/env node

const CocoCompiler = require('../index.js');
const process = require('process');

async function main(args) {
  const { buildingOptions, compilingOptions } = parseArguments(args);
  const coco = new CocoCompiler(buildingOptions.inputFile, buildingOptions.outputFile, buildingOptions.cppFile, compilingOptions)
  try {
    if (buildingOptions.version) {
      coco.printVersion();
    } else if (buildingOptions.inputFile) {
      console.time("Building cpp");
      await coco.buildCpp();
      console.timeEnd("Building cpp");
      console.time("Compiling cpp");
      await coco.compile();
      console.timeEnd("Compiling cpp");
      console.time("Running exe");
      await coco.run();
      console.timeEnd("Running exe");
    } else {
      coco.printUsage();
    }
  } catch (error) {
    console.error("An error occurred:", error);
    process.exit(1);
  }
}

function parseArguments(args) {
  const buildingOptions = {
    version: false,
    inputFile: '',
    outputFile: '',
    cppFile: '',
  };
  const compilingOptions = {
    numberDataType: 'int'
  };

  for (let i = 0; i < args.length; i++) {
    const arg = args[i];

    switch (arg) {
      case '-v':
      case '--version':
        buildingOptions.version = true;
        break;

      case '-o':
      case '--output':
        buildingOptions.outputFile = args[i + 1] || '';
        i++;
        break;

      case '--cpp':
        buildingOptions.cppFile = args[i + 1] || '';
        i++;
        break;

      case '--useFloat':
      case '--useBigInt':
        compilingOptions.numberDataType = "double"

      default:
        buildingOptions.inputFile = arg;
        break;
    }
  }

  return { buildingOptions, compilingOptions };
}

main(process.argv.slice(2));
