const { expect, use } = require("chai")
const chaiString = require("chai-string")
const path = require("path")
const { spawn } = require("child_process")
const fs = require("fs").promises
const CocoCompiler = require("../../index.js")

use(chaiString)

describe("Given ALL JS methods", function () {
    this.timeout(10000000)
    describe("Given all built-in STRING methods", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("strings")
        })
    })
    describe("Given all built-in NUMBER methods", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("numbers")
        })
    })
    describe("Given all built-in GLOBAL methods", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("functions")
        })
    })
    describe("Given all built-in Array methods", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("arrays")
        })
    })
    describe("Given the Number Class Object", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("objects/Number")
        })
    })
    describe("Given the Math Class Object", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("objects/Math")
        })
    })
    describe("Given the Date Object", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("objects/Date")
        })
    })
    describe.only("Given the String Object", function () {
        it("Should output same results as node", async function () {
            await compileAndRunTest("objects/String")
        })
    })
})

describe.skip("Given the TEST SOLO file", function () {
    it("Should output same results as node", async function () {
        await compileAndRunTest("solo")
    })
})

function preprocessOutput(output) {
    // Replace single quotes with double quotes
    output = output.replace(/[']/g, '"');

    // Replace date formats with the desired format (e.g., MM/DD/YYYY to M/DD/YYYY)
    output = output.replace(/\b(\d{2})\/(\d{2})\/(\d{2})\b/g, (match, month, day, year) => {
        // Remove leading zeros from month and day
        return `${parseInt(month, 10)}/${parseInt(day, 10)}/20${year}`;
    });

    // Replace floating point numbers with no decimal part (e.g., 42.0 to 42)
    output = output.replace(/\b(\d+)\.0\b/g, "$1");

    return output;
}

async function compileAndRunTest(fileName) {
    const compileOptions = {
        inputFile: path.join(__dirname, `./input/${fileName}.js`),
        outputFile: path.join(__dirname, `./output/${fileName}.exe`),
        cppFile: path.join(__dirname, `./input/${fileName}.cc`),
    }
    const coco = new CocoCompiler(compileOptions, {
        numberDataType: "double",
    })

    await coco.buildCpp()
    await coco.compile()

    const cocoResult = await runInCoco(coco)

    const nodeResult = await runInNode(compileOptions.inputFile)

    expect(preprocessOutput(cocoResult)).to.equalIgnoreSpaces(
        preprocessOutput(nodeResult)
    )
    await cleanupFiles(compileOptions.cppFile, compileOptions.outputFile)
}

async function runInNode(input) {
    const childProcess = spawn(`node`, [input])
    let output = ""

    childProcess.stdout.on("data", (data) => {
        output += data
    })

    await new Promise((resolve) => {
        childProcess.on("close", (code) => {
            resolve()
        })
    })

    return output
}

async function runInCoco(coco) {
    const result = await coco.run(true)
    return result
}

async function cleanupFiles(...files) {
    for (const file of files) {
        await fs.unlink(file)
    }
}
