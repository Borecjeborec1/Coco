const acorn = require("acorn");
const { tsPlugin } = require("acorn-typescript");
const fs = require("fs");
const path = require("path");
const { exec, spawn } = require("child_process");

const { generateWholeCode } = require("./src/main.js");

async function executeCommand(command, errorMessage) {
    return new Promise((resolve, reject) => {
        exec(command, (error, stdout, stderr) => {
            if (error) {
                reject(new Error(`${errorMessage}: ${error.message}`));
                return;
            }
            resolve({ stdout, stderr });
        });
    });
}

class CocoCompiler {
    constructor(
        _buildingOptions = { _cppFile: "./test/test.cc" },
        _compilingOptions = {}
    ) {
        this.inputFile = _buildingOptions.inputFile;
        this.outputFile =
            _buildingOptions.outputFile ||
            this.inputFile.replace(/\.js|\.ts|\.coco/, "");
        this.cppFile =
            _buildingOptions.cppFile ||
            this.inputFile.replace(/\.js|\.ts|\.coco/, ".cc");

        this.compilingOptions = {
            inputFile: this.inputFile,
            outputFile: this.outputFile,
            cppFile: this.cppFile,
            ..._compilingOptions,
        };
    }

    async buildCpp() {
        try {
            await fs.accessSync(this.inputFile);
        } catch (error) {
            this.printInputFileMissing(this.inputFile);
            throw error;
        }

        try {
            const code = fs.readFileSync(this.inputFile, "utf-8");
            const ast = acorn.Parser.extend(tsPlugin()).parse(code, {
                sourceType: "module",
                ecmaVersion: "latest",
                locations: true,
            });
            const res = generateWholeCode(ast, this.compilingOptions);
            writeToFileSafely(this.cppFile, res);
            createFolderSafely(this.outputFile);
            copyFolder(
                path.join(__dirname, `./src/lib/C++/`),
                path.join(path.dirname(this.cppFile), `lib/`)
            );
        } catch (error) {
            throw new Error(`Error building C++ with Coco: ${error.message}`);
        }
    }

    async compile() {
        try {
            const compileCommand = `g++ ${this.cppFile} -s -o ${this.outputFile} -O3 -ffast-math`;
            await executeCommand(
                compileCommand,
                "Error compiling C++ with Coco"
            );
        } catch (error) {
            this.printCompilingError(error);
            throw error;
        }
    }

    async run(_returnResult = false) {
        const outputPath = this.outputFile;
        const childProcess = spawn(outputPath);
        let output = "";

        childProcess.stdout.on("data", (data) => {
            if (_returnResult) {
                output += data;
            } else {
                console.log(`${data}`);
            }
        });

        childProcess.stderr.on("data", (data) => {
            console.error(`Error: ${data}`);
        });

        try {
            await new Promise((resolve) => {
                childProcess.on("close", (code) => {
                    resolve();
                });
            });
        } catch (error) {
            this.printRunningBinaryError(error);
            throw error;
        } finally {
            process.on("exit", () => {
                childProcess.kill();
            });
        }

        return output;
    }

    printVersion() {
        const packageJson = require("./package.json");
        console.log(`Version: ${packageJson.version}`);
    }

    printUsage() {
        console.log("Usage:");
        console.log("-v, --version: Print the version");
        console.log(
            "-o, --output <file>: Compile with the specified output file"
        );
        console.log("Example:");
        console.log("mypackage inputFile.js");
        console.log("mypackage -v");
        console.log("mypackage inputFile.js -o outputFile.cc");
    }

    printInputFileMissing(inputFile) {
        console.error(
            `Error: The input file "${inputFile}" does not exist or is inaccessible.`
        );
        console.error(
            "Please ensure that the specified input file path is correct and that you have the necessary permissions to access it."
        );
    }
    printCompilingError(error) {
        console.error("Error compiling C++ with Coco: ", error.message);
    }
    printRunningBinaryError(error) {
        console.error("Error running C++ executable:", error.message);
    }
}

function writeToFileSafely(filePath, data) {
    createFolderSafely(filePath);
    fs.writeFileSync(filePath, data, "utf-8");
}

function createFolderSafely(folderPath) {
    const destinationFolder = path.dirname(folderPath);

    if (!fs.existsSync(destinationFolder)) {
        fs.mkdirSync(destinationFolder, { recursive: true });
    }
}

function copyFolder(sourceFolder, destinationFolder) {
    if (!fs.existsSync(destinationFolder)) {
        fs.mkdirSync(destinationFolder, { recursive: true });
    }

    const files = fs.readdirSync(sourceFolder);
    files.forEach((fileName) => {
        const sourceFilePath = path.join(sourceFolder, fileName);
        const destinationFilePath = path.join(destinationFolder, fileName);

        if (fs.lstatSync(sourceFilePath).isDirectory()) {
            copyFolder(sourceFilePath, destinationFilePath);
        } else {
            fs.copyFileSync(sourceFilePath, destinationFilePath);
        }
    });
}

module.exports = CocoCompiler;
