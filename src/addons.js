const fs = require("fs")
const path = require('path');

function loadLibFiles() {
  const libFolderPath = path.join(__dirname, './lib');
  const files = fs.readdirSync(libFolderPath);

  let combinedContent = '';

  files.forEach(file => {
    if (path.extname(file) === '.hh') {
      const filePath = path.join(libFolderPath, file);
      const fileContent = fs.readFileSync(filePath, 'utf-8');
      combinedContent += fileContent;
    }
  });

  return combinedContent;
}
function joinCppParts(mainBody = "", fcDefinitions = "", usedTypenames, includes = ["iostream"]) {
  let allIncludes = ""
  for (let i in includes) {
    allIncludes += `#include <${includes[i]}>\n`
  }
  return `
// All new includes goes here
${allIncludes}

// All JSMethods goes here
${loadLibFiles()}

// All functions with its argument templates goes here
${generateTemplates(usedTypenames)}
${fcDefinitions} 

// Main Function (Have to be the only main function)
int main(){
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