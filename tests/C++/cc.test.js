const { expect, use } = require('chai');
const chaiString = require('chai-string');
const path = require('path');
const { spawn } = require('child_process');
const fs = require('fs').promises;
const CocoCompiler = require('../../index.js');

use(chaiString);

describe('Given all string methods', function () {
  this.timeout(10000000);
  describe("Given all built-in string methods", function () {
    it('Should output same results as node', async function () {
      await compileAndRunTest("strings");
    });

  })
  describe('Given all built-in number methods', function () {
    it('Should output same results as node', async function () {

      await compileAndRunTest("numbers");
    });
  });

});




function preprocessOutput(output) {
  return output.replace(/[']/g, '"');
}

async function compileAndRunTest(fileName) {
  const jsFile = path.join(__dirname, `./input/${fileName}.js`);
  const ccFile = path.join(__dirname, `./input/${fileName}.cc`);
  const binaryFile = path.join(__dirname, `./output/${fileName}.exe`);

  const coco = new CocoCompiler(jsFile, binaryFile, ccFile);

  await coco.buildCpp();
  await coco.compile();

  const cocoResult = await runInCoco(coco);

  const nodeResult = await runInNode(jsFile);

  expect(preprocessOutput(cocoResult)).to.equalIgnoreSpaces(preprocessOutput(nodeResult));

  await cleanupFiles(ccFile, binaryFile);
}

async function runInNode(input) {
  const childProcess = spawn(`node`, [input]);
  let output = '';

  childProcess.stdout.on('data', (data) => {
    output += data;
  });

  await new Promise((resolve) => {
    childProcess.on('close', (code) => {
      resolve();
    });
  });

  return output;
}

async function runInCoco(coco) {
  const result = await coco.run(true);
  return result;
}

async function cleanupFiles(...files) {
  for (const file of files) {
    await fs.unlink(file);
  }
}