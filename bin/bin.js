#!/usr/bin/env node

const CocoCompiler = require("../index.js")
const process = require("process")

async function main(_args) {
    const { runtimeOptions, buildingOptions, compilingOptions } =
        parseArguments(_args)
    const coco = new CocoCompiler(buildingOptions, compilingOptions)

    if (runtimeOptions.version) return coco.printVersion()

    if (buildingOptions.inputFile) {
        if (runtimeOptions.timeOutput) {
            timeOperation("Building cpp", async () => await coco.buildCpp())
            timeOperation("Compiling cpp", async () => await coco.compile())
            timeOperation("Running exe", async () => await coco.run())
            return
        } else {
            await coco.buildCpp()
            await coco.compile()
            await coco.run()
            return
        }
    }

    coco.printUsage()
}

function parseArguments(_args) {
    const runtimeOptions = {
        version: false,
        timeOutputs: false,
    }
    const buildingOptions = {
        inputFile: "",
        outputFile: "",
        cppFile: "",
    }
    const compilingOptions = {
        numberDataType: "int",
    }

    for (let i = 0; i < _args.length; i++) {
        const arg = _args[i]

        switch (arg) {
            case "-v":
            case "--version":
                runtimeOptions.version = true
                break
            case "--time-output":
            case "--time-outputs":
                runtimeOptions.timeOutputs = true
                break

            case "-o":
            case "--output":
                buildingOptions.outputFile = _args[i + 1] || ""
                i++
                break

            case "--cpp":
                buildingOptions.cppFile = _args[i + 1] || ""
                i++
                break

            case "--useFloat":
            case "--useBigInt":
                compilingOptions.numberDataType = "double"

            default:
                buildingOptions.inputFile = arg
                break
        }
    }

    return { runtimeOptions, buildingOptions, compilingOptions }
}

function timeOperation(label, operation) {
    console.time(label)
    operation()
        .then(() => console.timeEnd(label))
        .catch((error) => handleError(error))
}

function handleError(error) {
    console.error("An error occurred:", error)
    process.exit(1)
}

main(process.argv.slice(2))
