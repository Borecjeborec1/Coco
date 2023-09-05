const acorn = require('acorn');
const fs = require('fs').promises;
const path = require('path');
const { promisify } = require('util');
const { exec, spawn } = require('child_process');

const { generateWholeCode } = require('./src/main.js');

class CocoCompiler {
  constructor(_inputFile, _outputFile, _cppFile = "./test/test.cc", _compilingOptions = {}) {
    this.inputFile = _inputFile;
    this.outputFile = _outputFile || this.inputFile.replace('.js', '');
    this.cppFile = _cppFile || this.inputFile.replace('.js', '.cc');
    this.compilingOptions = _compilingOptions
  }


  async buildCpp() {
    if (! await this.fileExists(this.inputFile))
      return this.printInputFileMissing();

    try {
      const code = await fs.readFile(this.inputFile, 'utf-8');
      const ast = acorn.parse(code);
      const res = generateWholeCode(ast, this.compilingOptions);
      await fs.writeFile(this.cppFile, res);
    } catch (error) {
      throw new Error(`Error building C++ with Coco: ${error.message}`);
    }

  }

  async compile() {
    try {
      const compileCommand = `g++ ${this.cppFile} -s -o ${this.outputFile} -O3 -ffast-math`;
      const execPromise = promisify(exec);
      await execPromise(compileCommand);
    } catch (error) {
      throw new Error(`Error compiling C++ with Coco: ${error.message}`);
    }
  }

  async run(returnResult = false) {
    const outputPath = this.outputFile;
    const childProcess = spawn(outputPath);
    let output = '';

    childProcess.stdout.on('data', (data) => {
      if (returnResult) {
        output += data;
      } else {
        console.log(`${data}`);
      }
    });

    childProcess.stderr.on('data', (data) => {
      console.error(`Error: ${data}`);
    });


    await new Promise((resolve) => {
      childProcess.on('close', (code) => {
        resolve();
      });
    });

    process.on("exit", () => {
      childProcess.kill()
    })

    return output;
  }

  async fileExists(filePath) {
    try {
      await fs.access(filePath);
      return true;
    } catch (error) {
      return false;
    }
  }

  printVersion() {
    const packageJson = require('./package.json');
    console.log(`Version: ${packageJson.version}`);
  }

  printUsage() {
    console.log('Usage:');
    console.log('-v, --version: Print the version');
    console.log('-o, --output <file>: Compile with the specified output file');
    console.log('Example:');
    console.log('mypackage inputFile.js');
    console.log('mypackage -v');
    console.log('mypackage inputFile.js -o outputFile.cc');
  }
  printInputFileMissing() {
    console.log('Input file is missing');
    //TODO: Make this log better
  }
}

module.exports = CocoCompiler;
