const fs = require("fs")
const path = require('path');

function loadLibFiles(libFolderPath) {
  let combinedContent = '';
  let nlohmannJsonContent = ''; // To store content of nlohmann-json file

  function processFile(filePath) {
    const fileContent = fs.readFileSync(filePath, 'utf-8');
    if (path.basename(filePath) === 'nlohmann-json.hh') {
      nlohmannJsonContent = "\n" + fileContent;
    } else if (path.extname(filePath) === '.hh' || path.extname(filePath) === '.hpp') {
      combinedContent += "\n" + fileContent.replace('#include "nlohmann-json.hpp"', "");
    }
  }

  function exploreFolder(folderPath) {
    const files = fs.readdirSync(folderPath);

    files.forEach(file => {
      const filePath = path.join(folderPath, file);
      const stats = fs.statSync(filePath);

      if (stats.isDirectory()) {
        exploreFolder(filePath); // Recurse into subfolder
      } else {
        processFile(filePath);
      }
    });
  }

  exploreFolder(libFolderPath);
  combinedContent = nlohmannJsonContent + "\n" + combinedContent; // Add nlohmann-json content at the start
  return combinedContent;
}


function joinCppParts(mainBody = "", fcDefinitions = "", usedTypenames, includes = ["iostream", "chrono"]) {
  let allIncludes = ""
  for (let i in includes) {
    allIncludes += `#include <${includes[i]}>\n`
  }
  return `
// All new includes goes here
${allIncludes}

// All JSMethods goes here
${loadLibFiles(path.join(__dirname, './lib'))}

// All functions with its argument templates goes here
${generateTemplates(usedTypenames)}
${fcDefinitions} 

// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  ${mainBody}
  return 0;
}  
`
}

function generateTypename() {
  const LENGTH = 4
  const LETTERS = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
  let typename = ""
  while (typename.length < LENGTH) {
    typename += LETTERS[Math.floor(Math.random() * LETTERS.length)]
  }
  return typename
}

function generateTemplates(typenames) {
  if (!typenames.length)
    return ""
  let templates = "template < "
  for (let i = 0; i < typenames.length; ++i) {
    if (i == 0)
      templates += `typename ${typenames[i]}`
    else
      templates += `, typename ${typenames[i]}`
  }
  return templates + ">"
}




module.exports = { joinCppParts, generateTypename }