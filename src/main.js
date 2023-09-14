const fs = require("fs")
const path = require('path');

const { BUILTIN_JS_FUNCTIONS } = require("./lib/JS/Builtin-functions.js")

let config = { numberDataType: 'int' }

function generateWholeCode(ast, compilingOptions) {
  config = { ...config, ...compilingOptions }
  const mainBody = generateCpp(ast);
  return joinCppParts(mainBody)
}
const validUserTypes = { int: "int", float: "double", string: "std::string", void: "void", json: "nlohman::json", boolean: "bool" }
function mapUserType(type) {
  return validUserTypes[type]
}


function generateCpp(ast, compilingOptions) {
  config = { ...config, ...compilingOptions }
  try {
    // console.log("Translating:: " + ast.type)
    let x = ast.type
  } catch (er) {
    console.log("er no type: " + er)
    return ""
  }
  switch (ast.type) {
    case "Program":
      return ast.body.map(generateCpp).join("\n");
    case "FunctionDeclaration": {
      const funcName = generateCpp(ast.id);
      const params = ast.params.map(generateCpp).map(el => "auto " + el).join(", ");
      const body = generateCpp(ast.body);
      return `auto ${funcName} = [](${params}) { \n${body} \n };`;
    }
    case "BlockStatement": {
      return ast.body.map(generateCpp).join("\n")
    }
    case "VariableDeclaration": {
      const declarations = ast.declarations.map(generateCpp).join(", ");
      const typeAnnotation = ast.declarations[0].id.typeAnnotation;
      const type = typeAnnotation ? generateCpp(typeAnnotation.typeAnnotation) : "";
      const declarationType = mapUserType(type) ? mapUserType(type) : "auto"; // Handle const declaration

      return `${declarationType} ${declarations}; \n`;
    }
    case "VariableDeclarator":
      if (ast.id.typeAnnotation) {
        return `${generateCpp(ast.id)} = ${ast.init.raw} `
      }
      return `${generateCpp(ast.id)} = ${generateCpp(ast.init)} `;
    case "Identifier":
      return ast.name;
    case "Literal": {
      console.log("LITERALLLLLLLLLLL:::: ", ast)
      if (ast.typeAnnotation) {
        return ast.value.toString();
      }
      if (ast.value.toString().startsWith("/")) {
        if (/\/(.+)\/([a-z]*)/.test(ast.value)) { // Check if it's a regex
          const [, pattern, flags] = ast.value.toString().match(/\/(.+)\/([a-z]*)/);
          let regexFlags = "std::regex::ECMAScript";
          if (flags.includes("i")) regexFlags += " | std::regex::icase";
          if (flags.includes("m")) regexFlags += " | std::regex::multiline";
          if (flags.includes("s")) regexFlags += " | std::regex::dotall";
          if (flags.includes("x")) regexFlags += " | std::regex::extended";
          if (flags.includes("U")) regexFlags += " | std::regex::ungreedy";

          return `std::regex("${pattern}", ${regexFlags})`;
        }
      }
      if (typeof ast.value === 'string') {
        return `std::string("${ast.value}")`;
      } else if (typeof ast.value === 'number') {
        return `static_cast<${config.numberDataType}>(${ast.value})`;
      } else if (typeof ast.value === "boolean") {
        return `${!!ast.value}`;
      }
      return `// Unknown type: ${JSON.stringify(ast)}`;
    }

    case "BinaryExpression": {
      if (ast.operator === "**") {
        const left = generateCpp(ast.left);
        const right = generateCpp(ast.right);
        return `std::pow(${left}, ${right})`;
      } else if (ast.operator === "===") {
        return `(${generateCpp(ast.left)} == ${generateCpp(ast.right)})`;
      } else if (ast.operator === "!==")
        return `(${generateCpp(ast.left)} != ${generateCpp(ast.right)})`;

      return `(${generateCpp(ast.left)} ${ast.operator} ${generateCpp(ast.right)})`;
    }
    case "ReturnStatement":

      return `return ${generateCpp(ast.argument)}; `;
    case "CallExpression": {
      const callee = generateCpp(ast.callee);

      if (ast.callee.type === 'MemberExpression' && ast.callee.property && ast.callee.object) {
        if (ast.callee.object.name === "console") {
          if (ast.type === "CallExpression" && ast.callee.type === "MemberExpression" && ast.callee.object.name === "console") {
            let args = ast.arguments.map(generateCpp).join(" << ");
            let typeOfCout = ast.callee.property.name === "error" ? "cerr" : "cout"
            if (ast.callee.property.name === "time") {
              const label = ast.expression.arguments[0].value;
              return `auto ${label} = std::chrono::high_resolution_clock::now();\n return;`;
            }

            if (ast.callee.property.name === "timeEnd") {
              const label = ast.arguments[0].value;
              return `
              auto end_time = std::chrono::high_resolution_clock::now();
              auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                  end_time - ${label});
            
              std::cout << "${label}: " << duration.count() << "ms" << std::endl;
              return;
              `;
            }
            return `std::${typeOfCout} << ${args} << '\\n';\nreturn;`;
          }
        }


        let jsFunction = BUILTIN_JS_FUNCTIONS[ast.callee.property.name];
        let variableName = ast.callee.object.name || generateCpp(ast.callee.object) // Ensure that nested methods get called right
        if (jsFunction) {
          const { name, argCount } = jsFunction;
          if (ast.arguments && ast.arguments.length > 0) {
            const args = ast.arguments.slice(0, argCount).map(generateCpp).join(', ');
            return `${name}(${variableName}, ${args})`;
          } else {
            return `${name}(${variableName})`;
          }
        }
      }
      return `${callee}(${ast.arguments.map(generateCpp).join(', ')})`;
    }
    case "FunctionExpression":
      return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(", ")}) { \n${generateCpp(ast.body)} \n } `;
    case "ArrowFunctionExpression": {
      if (ast.body.type === "BlockStatement")
        return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(", ")}) { \n${generateCpp(ast.body)} \n } `;

      const returnBody = generateCpp(ast.body)
      const returnString = returnBody.includes("return;") ? `${returnBody}` : `return ${returnBody};`

      return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(", ")}) { ${returnString} } `;
    }
    case 'MemberExpression': {
      const objectCode = generateCpp(ast.object);
      const propertyCode = generateCpp(ast.property);
      if (propertyCode === 'length') {
        return `${objectCode}.length()`;
      } else if (propertyCode.startsWith("std::string(")) {
        let propertyString = propertyCode.replace(/std\:\:string\(|\)/g, "")
        return `${objectCode}[${propertyString}]`;
      } else if (propertyCode.startsWith(`static_cast<${config.numberDataType}>(`)) {
        const staticCastRegex = new RegExp(`static_cast<${config.numberDataType}>(\|)`, "g");
        let propertyString = propertyCode.replace(staticCastRegex, "")
        return `${objectCode}[${propertyString}]`;
      } else if (objectCode == "this") {
        return `${propertyCode}`
      } else {
        return `${objectCode}["${propertyCode}"]`;
      }
    }
    case "IfStatement": {
      let result = `if (${generateCpp(ast.test)}) {\n${generateCpp(ast.consequent)}\n}`;
      if (ast.alternate) {
        if (ast.alternate.type === "IfStatement") {
          result += ` else ${generateCpp(ast.alternate)}`;
        } else {
          result += ` else {\n${generateCpp(ast.alternate)}\n}`;
        }
      }
      return result;
    }
    case "UnaryExpression": {
      let operator = ast.operator;
      let argument = generateCpp(ast.argument);
      if (operator === "typeof") {
        return `typeid(${argument}).name()`;
      } else if (operator === "-") {
        return `static_cast<${config.numberDataType}>(0)-${argument}`;
      }
      return `${operator}${argument} `;
    }
    case "AssignmentExpression": {
      return `${generateCpp(ast.left)} ${ast.operator} ${generateCpp(ast.right)}`;
    }
    case "ObjectExpression": {
      let properties = ast.properties.map(property => `{"${generateCpp(property.key)}", ${generateCpp(property.value)}}`).join(", ");
      return `nlohmann::json{${properties}}`;
    }
    case "Property":
      return `{"${generateCpp(ast.key)}", ${generateCpp(ast.value)}}`;
    case "ArrayExpression": {
      let elements = ast.elements.map(generateCpp).join(", ");
      return `nlohmann::json{${elements}}`;
    }
    case "EmptyStatement": {
      return ";";
    }
    case "ExpressionStatement": {
      if (ast.expression.type === "CallExpression" && ast.expression.callee.type === "MemberExpression" && ast.expression.callee.object.name === "console") {
        let args = ast.expression.arguments.map(generateCpp).join(" << ");
        let typeOfCout = "cout"
        if (ast.expression.callee.property.name === "time") {
          const label = ast.expression.arguments[0].value;
          return `auto ${label} = std::chrono::high_resolution_clock::now();`;
        } else if (ast.expression.callee.property.name === "timeEnd") {
          const label = ast.expression.arguments[0].value;
          return `
          auto end_time = std::chrono::high_resolution_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
              end_time - ${label});
        
          std::cout << "${label}: " << duration.count() << "ms" << std::endl;
          `;
        } else if (ast.expression.callee.property.name === "error") {
          typeOfCout = "cerr"
        }
        return `std::${typeOfCout} << ${args} << '\\n';`;
      } else {
        return generateCpp(ast.expression) + ";";
      }
    }
    case "ForStatement": {
      let init = generateCpp(ast.init);
      let test = generateCpp(ast.test);
      let update = generateCpp(ast.update);
      let body = generateCpp(ast.body);
      return `for (${init} ${test}; ${update}) { \n${body} \n } `;
    }
    case "ForInStatement": {
      const left = generateCpp(ast.left.declarations[0].id);
      const right = generateCpp(ast.right);
      const body = generateCpp(ast.body);
      return `for (const auto& entry : ${right}) {
        auto ${left} = entry.first;
        ${body}
      }`;
    }
    case "ForOfStatement": {
      const right = generateCpp(ast.right);
      const body = generateCpp(ast.body);
      if (ast.left.declarations[0].id.elements) {// array of keys inside loop
        const index = ast.left.declarations[0].id.elements[0].name
        const value = ast.left.declarations[0].id.elements[1].name
        return `
        int ${index} = 0;
        for (const auto&  __val__ : ${right}) {
          auto ${value} = __val__[1];
          ${body}
          ${index}+=1;
        }`;
      }
      const left = generateCpp(ast.left.declarations[0].id);
      return `for (const auto& ${left} : ${right}) {
        ${body}
      }`;
    }
    case "WhileStatement":
      return `while (${generateCpp(ast.test)}) { \n${generateCpp(ast.body)} } \n`;
    case "DoWhileStatement":
      return `do { \n${generateCpp(ast.body)} } while (${generateCpp(ast.test)}); \n`;
    case "UpdateExpression": {
      let operator = ast.operator === "++" ? "++" : "--";
      let argument = generateCpp(ast.argument);
      return `${argument}${operator} `;
    }
    case "LogicalExpression": {
      let left = generateCpp(ast.left);
      let right = generateCpp(ast.right);
      let operator = ast.operator === "&&" ? "&&" : "||";
      return `(${left} ${operator} ${right})`;
    }
    case "ConditionalExpression": {
      let test = generateCpp(ast.test);
      let consequent = generateCpp(ast.consequent);
      let alternate = generateCpp(ast.alternate);
      return `(${test} ? ${consequent} : ${alternate})`;
    }
    case "SwitchStatement": {
      const test = generateCpp(ast.discriminant);
      const cases = ast.cases.map(c => generateCpp(c)).join("\n");
      return `switch (${test}) { \n${cases} } \n`;
    }
    case "SwitchCase": {
      if (ast.test) {
        const test = generateCpp(ast.test);
        const consequent = ast.consequent.map(c => generateCpp(c)).join("\n");
        return `case ${test}: \n${consequent} `;
      } else {
        const consequent = ast.consequent.map(c => generateCpp(c)).join("\n");
        return `default: \n${consequent} `;
      }
    }
    case "BreakStatement":
      return "break;\n";
    case "ContinueStatement":
      return "continue;\n";
    case "ThisExpression":
      return "this";
    case "NewExpression": {
      const callee = generateCpp(ast.callee);
      const args = ast.arguments.map(a => generateCpp(a)).join(", ");
      return `new ${callee} (${args})`;
    }
    case "ThrowStatement": {
      const argument = generateCpp(ast.argument);
      return `throw ${argument}; \n`;
    }
    case "TryStatement": {
      const block = generateCpp(ast.block);
      const handler = ast.handler
        ? `catch (${generateCpp(ast.handler.param)}) { \n${generateCpp(ast.handler.body)} } \n`
        : "";
      const finalizer = ast.finalizer ? `finally { \n${generateCpp(ast.finalizer)} } \n` : "";
      return `try { \n${block} } ${handler}${finalizer} `;
    }
    case "CatchClause": {
      const param = generateCpp(ast.param);
      const body = generateCpp(ast.body);
      return `catch (${param}) { \n${body} } \n`;
    }
    case "SpreadElement": {
      const argument = generateCpp(ast.argument);
      return `std:: copy(${argument}.begin(), ${argument}.end(), std:: back_inserter(${argument}_vector)); \n`;
    }
    case "RestElement": {
      const argName = generateCpp(ast.argument);
      const paramName = argName.startsWith("&") ? argName.substring(1) : argName;
      return
      // return `std:: vector < ${getCppType(ast.argument.elements[0].type)}> ${paramName} _vector(${argName}); \n`;
    }
    case "TemplateLiteral": {
      const quasis = ast.quasis.map(generateCpp);
      const expressions = ast.expressions.map(expression => generateCpp(expression));
      let result = ``;

      for (let i = 0; i < expressions.length; i++) {
        result += `${quasis[i]},  `
        result += `${expressions[i]},  `
      }
      return `JS_join(nlohmann::json{${result}},"")`;
    }
    case "TemplateElement":
      return `"${ast.value.raw}"`;
    case "RegExpLiteral": {
      const pattern = ast.pattern;
      const flags = ast.flags;
      return `std::regex("${pattern}", std::regex::${flags})`;
    }
    case "TSTypeAnnotation": {
      return generateCpp(ast.typeAnnotation);
    }
    case "TSTypeReference": {
      const typeName = generateCpp(ast.typeName);
      return typeName;
    }

    // case "ClassDeclaration": {
    //   console.log("here")
    //   const className = generateCpp(ast.id);
    //   let constructorParams = ""
    //   let constructorInits = ""
    //   let constructorInitClass = ` class local_class {
    //     public:
    //       REPLACE_CONTENT
    // } local;`
    //   let classMethods = ""
    //   for (let i = 0; i < ast.body.body.length; ++i) {
    //     const generated = generateCpp(ast.body.body[i])
    //     console.log(generated)
    //     if (generated.isConstructor) {
    //       constructorInits = generated.constructorInits
    //       constructorInitClass = constructorInitClass.replace("REPLACE_CONTENT", constructorInits.split("\n").map(row => {
    //         let items = row.split("=")
    //         return `decltype(${items[1]}) ${items[0]}`
    //       }).join("\n"))
    //       constructorParams = generated.constructorParams
    //     } else {
    //       classMethods += generated.classMethod + "\n"
    //     }
    //   }
    //   console.log(`auto ${className} = [](${constructorParams}) {\n ${constructorInitClass}\n${constructorInits} \n ${classMethods}\n};`)
    //   return `auto ${className} = [](${constructorParams}) {\n ${constructorInitClass}\n${constructorInits} \n ${classMethods}\n};`;
    // }

    // case "MethodDefinition": {
    //   if (ast.kind === "constructor") {
    //     const constructorParams = ast.value.params.map(generateCpp).map(el => "auto " + el).join(", ");
    //     const body = generateCpp(ast.value.body);
    //     const constructorInits = body.replace(/this\./g, 'local.');
    //     console.log("HERE", constructorInits)
    //     return { constructorInits, isConstructor: true, constructorParams };
    //   } else {
    //     const methodName = ast.key.name;
    //     const params = ast.value.params.map(generateCpp).map(el => "auto " + el).join(", ");
    //     console.log(params)
    //     const body = generateCpp(ast.value.body);
    //     const modifiedBody = body.replace(/this\./g, '');
    //     return { classMethod: `auto ${methodName}(${params}) {\n${modifiedBody}\n}`, isConstructor: false };
    //   }
    // }
    default:
      console.log(`Unsupported AST node type: ${ast.type} `);
  }
}


function loadLibFiles(libFolderPath) {
  let combinedContent = '';
  let nlohmannJsonContent = ''; // To store content of nlohmann-json file
  const includes = []
  function processFile(filePath) {
    const fileContent = fs.readFileSync(filePath, 'utf-8');
    if (path.basename(filePath) === 'nlohmann-json.hh') {
      nlohmannJsonContent = "\n" + fileContent;
    } else if (path.extname(filePath) === '.hh' || path.extname(filePath) === '.hpp') {
      const regex = /\/\/ Ignore imports\r\n([\s\S]*?)\/\/ Ignore imports end/g;

      const modifiedInput = fileContent.toString().replace(regex, (match, capturedContent) => {
        includes.push(capturedContent);
        return "";
      });
      combinedContent += "\n" + modifiedInput

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
  function filterImports(e) {
    return e && !nlohmannJsonContent.includes(e) && !e.includes("hh") && e.includes("#include")
  }
  exploreFolder(libFolderPath);
  const nonDuplicateImports = [...new Set(includes.join("\n").split("\r\n"))];
  const filteredImports = nonDuplicateImports.filter(filterImports).join("\n");

  return {
    loadedLibFiles: filteredImports + "\n" + nlohmannJsonContent + "\n" + combinedContent,
    neededExternalImports: filteredImports
  };



}

function joinCppParts(mainBody = "") {

  const { loadedLibFiles, neededExternalImports } = loadLibFiles(path.join(__dirname, './lib/C++'))
  const neededImports = `#include <chrono>`

  return `

// All includes goes here
${neededExternalImports}
${neededImports}

// All Built-in JSMethods goes here
${loadedLibFiles}

// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  ${mainBody}
  return 0;
}  
`
}


module.exports = { generateWholeCode, generateCpp }