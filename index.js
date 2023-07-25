const acorn = require('acorn');
const fs = require("fs")
const path = require('path');
const { exec, spawn } = require('child_process');

let { generateWholeCode } = require("./src/main.js")
const settings = {}

exports.init = async (_inputFile, _outputFile = "") => {
  if (fs.existsSync(_inputFile)) {
    settings.input = _inputFile
    settings.output = _outputFile || _inputFile.replace(".js", ".cc")
    settings.binaryFile = settings.output.replace(/\.cc|\.cpp/, "")
    settings.binaryPath = path.join(process.cwd(), settings.binaryFile)
    let libFolder = path.join(__dirname, "lib")
    let distLibFolder = path.join(path.dirname(settings.output), "lib")
    copyFolderSync(libFolder, distLibFolder)
    fs.writeFileSync(settings.output, "Inited file")
  } else {
    console.log(`Could not find file called ${_inputFile}.`)
  }
}


exports.build = async () => {
  const code = fs.readFileSync(settings.input, "utf-8")
  const ast = acorn.parse(code);
  const res = generateWholeCode(ast)
  await fs.writeFileSync(settings.output, res)
}

exports.compile = async () => {

  const compileCommand = `g++ ${settings.output} -std=c++17 ./lib/types.cc -O3 -s -o ${settings.binaryFile} `;

  await new Promise((resolve, reject) => {
    exec(compileCommand, (error, stdout, stderr) => {
      if (error) {
        console.error(`Compilation failed: ${error.message}`);
        reject(error);
      } else if (stderr) {
        console.error(`Compilation error: ${stderr}`);
        reject(new Error(stderr));
      } else {
        console.log('Compilation successful');
        resolve();
      }
    });
  });

}

exports.run = async () => {
  const childProcess = spawn(settings.binaryPath);
  childProcess.stdout.on('data', (data) => {
    console.log(`${data}`);
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
};


function copyFolderSync(source, destination) {
  if (!fs.existsSync(destination)) {
    fs.mkdirSync(destination);
  }

  const files = fs.readdirSync(source);

  files.forEach((file) => {
    const sourcePath = path.join(source, file);
    const destinationPath = path.join(destination, file);

    if (fs.lstatSync(sourcePath).isFile()) {
      fs.copyFileSync(sourcePath, destinationPath);
    } else {
      copyFolder(sourcePath, destinationPath);
    }
  });
}