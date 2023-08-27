const acorn = require('acorn');
const fs = require('fs').promises;
const path = require('path');
const { promisify } = require('util');
const { exec, spawn } = require('child_process');

const { generateWholeCode } = require('./src/main.js');

class CocoCompiler {
  constructor(_inputFile, _outputFile, _cppFile = "./test/test.cc") {
    this.inputFile = _inputFile;
    this.outputFile = _outputFile || this.inputFile.replace('.js', '');
    console.log("Ozutput file: " + this.outputFile)
    this.cppFile = _cppFile || this.inputFile.replace('.js', '.cc');
    console.log("cpp file: " + this.cppFile)
  }


  async buildCpp() {
    if (! await this.fileExists(this.inputFile))
      return this.printInputFileMissing();

    try {
      const code = await fs.readFile(this.inputFile, 'utf-8');
      const ast = acorn.parse(code);
      const res = generateWholeCode(ast);
      await fs.writeFile(this.cppFile, res);
    } catch (error) {
      console.log('build error: ' + error);
    }

  }

  async compile() {
    try {
      const compileCommand = `g++ -O3 ${this.cppFile} -O3 -s -o ${this.outputFile}`;
      const execPromise = promisify(exec);
      await execPromise(compileCommand);
    } catch (error) {
      console.log('compile error: ' + error);
    }
  }

  async run() {
    const outputPath = path.join(process.cwd(), this.outputFile);
    const childProcess = spawn(outputPath);
    let output = '';

    childProcess.stdout.on('data', (data) => {
      console.log(`${data}`);
      output += data;
    });

    childProcess.stderr.on('data', (data) => {
      console.error(`Error: ${data}`);
    });

    await new Promise((resolve) => {
      childProcess.on('close', (code) => {
        console.log(`Child process exited with code ${code}`);
        resolve();
      });
    });

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
