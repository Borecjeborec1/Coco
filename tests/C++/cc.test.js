const { expect, use } = require('chai');
const chaiString = require('chai-string');
const CocoCompiler = require('../../index.js'); // Adjust the path accordingly
const path = require("path")
const { spawn } = require('child_process');
const fs = require("fs")

use(chaiString)

describe('Spawning cc tests', function () {
  this.timeout(10000000)
  it('it spawned', async function () {
    const jsFile = path.join(__dirname, "./input/strings.js")
    const ccFile = path.join(__dirname, "./input/strings.cc")
    const binaryFile = path.join(__dirname, "./output/strings.exe")
    const coco = new CocoCompiler(jsFile, binaryFile, ccFile);
    console.time("Building cpp")
    await coco.buildCpp()
    console.timeEnd("Building cpp")
    console.time("Compiling cpp")
    await coco.compile()
    console.timeEnd("Compiling cpp")
    console.time("Running exe")
    const cocoResult = await runInCoco(coco)
    console.timeEnd("Running exe")
    const nodeResult = await runInNode(jsFile)

    expect(cocoResult).to.equalIgnoreSpaces(nodeResult)
    // await cleanupFiles(binaryFile);
  });
});


async function runInNode(input) {
  const childProcess = spawn(`node`, [input]);
  let output = '';

  childProcess.stdout.on('data', (data) => {
    output += data;
  });

  await new Promise((resolve) => {
    childProcess.on('close', (code) => {
      console.log(`Child process exited with code ${code}`);
      resolve();
    });
  });

  return output;
}

async function runInCoco(coco) {
  const result = await coco.run(true);
  return result
}

async function cleanupFiles(...files) {
  for (const file of files) {
    await fs.unlinkSync(file);
  }
}