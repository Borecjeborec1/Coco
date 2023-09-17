const { expect, use } = require('chai');
const chaiString = require('chai-string');
const path = require('path');
const { spawn } = require('child_process');
const fs = require('fs').promises;
const CocoCompiler = require('../../index.js');

use(chaiString);

describe('Given ALL JS methods', function () {
  this.timeout(10000000);
  describe("Given all built-in STRING methods", function () {
    it('Should output same results as node', async function () {
      await compileAndRunTest("strings");
    });

  })
  describe('Given all built-in NUMBER methods', function () {
    it('Should output same results as node', async function () {

      await compileAndRunTest("numbers");
    });
  });
  describe('Given all built-in GLOBAL methods', function () {
    it('Should output same results as node', async function () {

      await compileAndRunTest("functions");
    });
  });
  describe.only('Given all built-in Array methods', function () {
    it('Should output same results as node', async function () {

      await compileAndRunTest("arrays");
    });
  });
});




function preprocessOutput(output) {
  return output.replace(/[']/g, '"').replace(/\b(\d+)\.0\b/g, '$1');
}

async function compileAndRunTest(fileName) {
  const jsFile = path.join(__dirname, `./input/${fileName}.js`);
  const ccFile = path.join(__dirname, `./input/${fileName}.cc`);
  const binaryFile = path.join(__dirname, `./output/${fileName}.exe`);

  const coco = new CocoCompiler(jsFile, binaryFile, ccFile, { numberDataType: 'double' });

  await coco.buildCpp();
  await coco.compile();

  const cocoResult = await runInCoco(coco);

  const nodeResult = await runInNode(jsFile);

  expect(preprocessOutput(cocoResult)).to.equalIgnoreSpaces(preprocessOutput(nodeResult));
  console.log("coco: ")
  console.log(preprocessOutput(cocoResult))
  console.log("nodejs: ")
  console.log(preprocessOutput(nodeResult))
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