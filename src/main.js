let { joinCppParts, generateTypename } = require("./addons.js")

const STRING_FUNCTIONS = {
  'charAt': { name: 'JS_charAt', argCount: 1 },
  'charCodeAt': { name: 'JS_charCodeAt', argCount: 1 },
  'concat': { name: 'JS_concat', argCount: Infinity },
  'includes': { name: 'JS_includes', argCount: 1 },
  'endsWith': { name: 'JS_endsWith', argCount: 1 },
  'indexOf': { name: 'JS_indexOf', argCount: 1 },
  'lastIndexOf': { name: 'JS_lastIndexOf', argCount: 1 },
  'localeCompare': { name: 'JS_localeCompare', argCount: 2 },
  'match': { name: 'JS_match', argCount: 1 },
  'matchAll': { name: 'JS_matchAll', argCount: 1 },
  'normalize': { name: 'JS_normalize', argCount: 1 },
  'padEnd': { name: 'JS_padEnd', argCount: 2 },
  'padStart': { name: 'JS_padStart', argCount: 2 },
  'repeat': { name: 'JS_repeat', argCount: 1 },
  'replace': { name: 'JS_replace', argCount: 2 },
  'search': { name: 'JS_search', argCount: 1 },
  'slice': { name: 'JS_slice', argCount: 2 },
  'split': { name: 'JS_split', argCount: 2 },
  'startsWith': { name: 'JS_startsWith', argCount: 1 },
  'substr': { name: 'JS_substr', argCount: 2 },
  'substring': { name: 'JS_substring', argCount: 2 },
  'toLocaleLowerCase': { name: 'JS_toLocaleLowerCase', argCount: 1 },
  'toLocaleUpperCase': { name: 'JS_toLocaleUpperCase', argCount: 1 },
  'toLowerCase': { name: 'JS_toLowerCase', argCount: 0 },
  'toUpperCase': { name: 'JS_toUpperCase', argCount: 0 },
  'toString': { name: 'JS_toString', argCount: 0 },
  'trim': { name: 'JS_trim', argCount: 0 },
  'trimEnd': { name: 'JS_trimEnd', argCount: 0 },
  'trimStart': { name: 'JS_trimStart', argCount: 0 },
};

const NUMBER_FUNCTIONS = {
  'toFixed': { name: 'JS_toFixed', argCount: 1 },
  'toExponential': { name: 'JS_toExponential', argCount: 1 },
  'toPrecision': { name: 'JS_toPrecision', argCount: 1 },
  'toString': { name: 'JS_toString', argCount: 1 },
  'valueOf': { name: 'JS_valueOf', argCount: 0 },
  'toLocaleString': { name: 'JS_toLocaleString', argCount: 0 },
  'isFinite': { name: 'JS_isFinite', argCount: 1 },
  'isNaN': { name: 'JS_isNaN', argCount: 1 },
  // 'parseInt': { name: 'JS_parseInt', argCount: 2 },
  // 'parseFloat': { name: 'JS_parseFloat', argCount: 1 },
};


const BOOLEAN_FUNCTIONS = {
  'toString': { name: 'JS_toString', argCount: 0 },
  'valueOf': { name: 'JS_valueOf', argCount: 0 },
};



const BUILTIN_JS_FUNCTIONS = { ...BOOLEAN_FUNCTIONS, ...NUMBER_FUNCTIONS, ...STRING_FUNCTIONS }

function generateWholeCode(ast) {

  const usedTypenames = []
  const fcDefinitons = []

  const mainBody = generateCpp(ast);
  const cppCode = joinCppParts(mainBody, fcDefinitons.join(""), usedTypenames)


  function generateCpp(ast) {
    try {
      // console.log("Translating:: " + ast.type)
    } catch (er) {
      console.log("er no type: " + er)
      return ""
    }
    switch (ast.type) {
      case "Program":
        return ast.body.map(generateCpp).join("\n");
      case "FunctionDeclaration": {
        const funcName = generateCpp(ast.id);
        const params = ast.params.map(param => {
          const paramType = generateTypename();
          const paramName = generateCpp(param);
          usedTypenames.push(paramType)
          return `${paramType} ${paramName}`;
        }).join(", ");
        const body = generateCpp(ast.body);
        fcDefinitons.push(`auto ${funcName}(${params}) { \n${body}}; \n`)
        return "";
      }
      case "BlockStatement":
        return ast.body.map(generateCpp).join("\n");
      case "VariableDeclaration": {
        const declarations = ast.declarations.map(generateCpp).join(", ");
        return `auto ${declarations}; \n`;
      }
      case "VariableDeclarator":
        return `${generateCpp(ast.id)} = ${generateCpp(ast.init)} `;
      case "Identifier":
        return ast.name;
      case "Literal": {
        if (typeof ast.value === 'string') {
          return `std::string("${ast.value}")`;
        } else if (typeof ast.value === 'number') {
          return `static_cast<double>(${ast.value})`;
        } else if (typeof ast.value === "boolean") {
          return `${!!ast.value}`;
        }
        return `// Unknown type: ${JSON.stringify(ast)}`

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

        const isMemberExpression = ast.callee.type === 'MemberExpression';
        if (isMemberExpression && ast.callee.property && ast.callee.object) {
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
        return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(", ")}) { return ${generateCpp(ast.body)}; } `;
      }
      case 'MemberExpression': {
        const objectCode = generateCpp(ast.object);
        const propertyCode = generateCpp(ast.property);

        return `${objectCode}.${propertyCode}`;
      }
      case "IfStatement": {
        let result = `if (${generateCpp(ast.test)}) { \n${generateCpp(ast.consequent)} \n } `;
        if (ast.alternate) {
          result += ` else { \n${generateCpp(ast.alternate)} \n } `;
        }
        return result;
      }
      case "UnaryExpression": {
        let operator = ast.operator;
        let argument = generateCpp(ast.argument);
        if (operator === "typeof")
          return `typeid(${argument}).name()`

        return `${operator}${argument} `;
      }
      case "AssignmentExpression": {
        return `${generateCpp(ast.left)} ${ast.operator} ${generateCpp(ast.right)} `;
      }
      case "ObjectExpression": {
        let properties = ast.properties.map(property => `${generateCpp(property.key)}: ${generateCpp(property.value)}`).join(", ");
        return `nlohmann::json{${properties}}`;
      }
      case "Property":
        return `${generateCpp(ast.key)}: ${generateCpp(ast.value)} `;
      case "ArrayExpression": {
        let elements = ast.elements.map(generateCpp).join(", ");
        return `JS_Array{${elements}}`;
      }
      case "EmptyStatement": {
        return ";";
      }
      case "ExpressionStatement": {
        if (ast.expression.type === "CallExpression" && ast.expression.callee.type === "MemberExpression" && ast.expression.callee.object.name === "console") {
          let args = ast.expression.arguments.map(generateCpp).join(" << ");
          let typeOfCout = "cout"
          if (ast.expression.callee.property.name === "error")
            typeOfCout = "cerr"
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
      default:
        console.log(`Unsupported AST node type: ${ast.type} `);
    }
  }


  return cppCode
}

module.exports = { generateWholeCode }