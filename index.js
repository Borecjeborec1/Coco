const acorn = require("acorn")
const { tsPlugin } = require("acorn-typescript")
const fs = require("fs").promises
const path = require("path")
const { exec, spawn } = require("child_process")

const { generateWholeCode } = require("./src/main.js")

async function executeCommand(command, errorMessage) {
    return new Promise((resolve, reject) => {
        exec(command, (error, stdout, stderr) => {
            if (error) {
                reject(new Error(`${errorMessage}: ${error.message}`))
                return
            }
            resolve({ stdout, stderr })
        })
    })
}

class CocoCompiler {
    constructor(
        _buildingOptions = { _cppFile: "./test/test.cc" },
        _compilingOptions = {}
    ) {
        this.inputFile = _buildingOptions.inputFile
        this.outputFile =
            _buildingOptions.outputFile ||
            this.inputFile.replace(/\.js|\.ts|\.coco/, "")
        this.cppFile =
            _buildingOptions.cppFile ||
            this.inputFile.replace(/\.js|\.ts|\.coco/, ".cc")
        this.jsonName = "nlohmann-json.hh"
        this.jsonInput = path.join(__dirname, `./src/lib/C++/${this.jsonName}`)
        this.jsonOutput = path.join(
            path.dirname(this.outputFile),
            `${this.jsonName}`
        )
        this.compilingOptions = _compilingOptions
    }

    async buildCpp() {
        try {
            await fs.access(this.inputFile)
        } catch (error) {
            this.printInputFileMissing(this.inputFile)
            throw error
        }

        try {
            const code = await fs.readFile(this.inputFile, "utf-8")
            const ast = acorn.Parser.extend(tsPlugin()).parse(code, {
                sourceType: "module",
                ecmaVersion: "latest",
                locations: true,
            })
            const res = generateWholeCode(ast, this.compilingOptions)
            await fs.writeFile(this.cppFile, res)
            await fs.copyFile(this.jsonInput, this.jsonOutput)
        } catch (error) {
            throw new Error(`Error building C++ with Coco: ${error.message}`)
        }
    }

    async compile() {
        try {
            const compileCommand = `g++ ${this.cppFile} -s -o ${this.outputFile} -O3 -ffast-math`
            await executeCommand(
                compileCommand,
                "Error compiling C++ with Coco"
            )
        } catch (error) {
            this.printCompilingError(error)
            throw error
        }
    }

    async run(_returnResult = false) {
        const outputPath = this.outputFile
        const childProcess = spawn(outputPath)
        let output = ""

        childProcess.stdout.on("data", (data) => {
            if (_returnResult) {
                output += data
            } else {
                console.log(`${data}`)
            }
        })

        childProcess.stderr.on("data", (data) => {
            console.error(`Error: ${data}`)
        })

        try {
            await new Promise((resolve) => {
                childProcess.on("close", (code) => {
                    resolve()
                })
            })
        } catch (error) {
            this.printRunningBinaryError(error)
            throw error
        } finally {
            process.on("exit", () => {
                childProcess.kill()
            })
        }

        return output
    }

    printVersion() {
        const packageJson = require("./package.json")
        console.log(`Version: ${packageJson.version}`)
    }

    printUsage() {
        console.log("Usage:")
        console.log("-v, --version: Print the version")
        console.log(
            "-o, --output <file>: Compile with the specified output file"
        )
        console.log("Example:")
        console.log("mypackage inputFile.js")
        console.log("mypackage -v")
        console.log("mypackage inputFile.js -o outputFile.cc")
    }

    printInputFileMissing(inputFile) {
        console.error(
            `Error: The input file "${inputFile}" does not exist or is inaccessible.`
        )
        console.error(
            "Please ensure that the specified input file path is correct and that you have the necessary permissions to access it."
        )
    }
    printCompilingError(error) {
        console.error("Error compiling C++ with Coco: ", error.message)
    }
    printRunningBinaryError(error) {
        console.error("Error running C++ executable:", error.message)
    }
}

module.exports = CocoCompiler
