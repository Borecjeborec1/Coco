const fs = require("fs")
const path = require('path');

function valueType(ast) {
  switch (ast.type) {
    case 'Literal':
      return ast.value === null ? 'std::nullptr_t' :
        typeof ast.value === 'string' ? 'std::string' :
          typeof ast.value === 'number' ? 'double' :
            typeof ast.value === 'boolean' ? 'bool' :
              'unsupported';
    case 'ArrayExpression':
      return `std::vector<${valueType(ast.elements[0])}>`;
    case 'ObjectExpression':
      return 'std::map<std::string, ' + valueType(ast.properties[0].value) + '>';
    default:
      return 'unsupported';
  }
}

function getCppType(jsType) {
  switch (jsType) {
    case 'string':
      return 'std::string';
    case 'number':
      return 'double';
    case 'boolean':
      return 'bool';
    case 'void':
      return 'void';
    case 'any':
      return 'auto';
    default:
      return jsType;
  }
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
${fs.readFileSync(path.join(__dirname, "./lib/JS_Functions.hh"), "utf-8")}

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
  let letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
  let typename = ""
  let len = 4
  while (typename.length < len) {
    typename += letters[Math.floor(Math.random() * letters.length)]
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




module.exports = { valueType, getCppType, joinCppParts, generateTypename }