let { isMethodOfArray, valueType, getCppType, joinCppParts, generateTypename } = require("./addons.js")

function generateWholeCode(ast) {

  const usedTypenames = []
  const fcDefinitons = []

  const mainBody = generateCpp(ast);
  const cppCode = joinCppParts(mainBody, fcDefinitons.join(""), usedTypenames)


  function generateCpp(ast) {
    try {
      if (!ast.type) {
        console.log(ast.type)
      }
    } catch (er) {
      console.log("er no type: " + er)
      return false
    }
    switch (ast.type) {
      case 'Program':
        return ast.body.map(generateCpp).join('\n');
      case 'FunctionDeclaration': {
        const funcName = generateCpp(ast.id);
        const params = ast.params.map(param => {
          const paramType = generateTypename();
          const paramName = generateCpp(param);
          usedTypenames.push(paramType)
          return `${paramType} ${paramName}`;
        }).join(', ');
        const body = generateCpp(ast.body);
        const returnType = getCppType(ast.returnType) || "auto";
        fcDefinitons.push(`${returnType} ${funcName}(${params}) { \n${body}}; \n`)
        return "";
      }
      case 'BlockStatement':
        return ast.body.map(generateCpp).join('\n');
      case 'VariableDeclaration': {
        const declarations = ast.declarations.map(generateCpp).join(', ');
        return `auto ${declarations}; \n`;
      }
      case 'VariableDeclarator':
        return `${generateCpp(ast.id)} = ${generateCpp(ast.init)} `;
      case 'Identifier':
        return ast.name;
      case 'Literal': {
        if (typeof ast.value === 'string') {
          return `JSString("${ast.value}")`;
        } else if (typeof ast.value === 'number') {
          return `JSNumber(${ast.value})`;
        } else if (typeof ast.value === 'boolean') {
          return `${!!ast.value}`;
        } else {
          return `// Unknown type: ${JSON.stringify(ast)}`
        }
      }
      case 'BinaryExpression': {
        if (ast.operator === '**') {
          const left = generateCpp(ast.left);
          const right = generateCpp(ast.right);
          return `std::pow(${left}, ${right})`;
        } else if (ast.operator === '===') {
          return `(${generateCpp(ast.left)} == ${generateCpp(ast.right)})`;
        } else if (ast.operator === '!==')
          return `(${generateCpp(ast.left)} != ${generateCpp(ast.right)})`;

        return `(${generateCpp(ast.left)} ${ast.operator} ${generateCpp(ast.right)})`;
      }
      case 'ReturnStatement':
        return `return ${generateCpp(ast.argument)}; `;
      case 'CallExpression': {
        let callee = generateCpp(ast.callee);
        let args = ast.arguments.map(generateCpp).join(', ');
        return `${callee}(${args})`;
      }
      case 'FunctionExpression':
        return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(', ')}) { \n${generateCpp(ast.body)} \n } `;
      case 'ArrowFunctionExpression': {
        if (ast.body.type === 'BlockStatement')
          return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(', ')}) { \n${generateCpp(ast.body)} \n } `;
        return `[](${ast.params.map(generateCpp).map(el => "auto " + el).join(', ')}) { return ${generateCpp(ast.body)}; } `;
      }
      case 'MemberExpression': {
        if (ast.object.type === 'Identifier' && ast.object.name === 'Math') {
          const property = ast.property.name;
          return `std::${property}`;
        }
        const object = generateCpp(ast.object);
        const property = generateCpp(ast.property);
        return `${object}.${property}`;
      }
      case 'IfStatement': {
        let result = `if (${generateCpp(ast.test)}) { \n${generateCpp(ast.consequent)} \n } `;
        if (ast.alternate) {
          result += ` else { \n${generateCpp(ast.alternate)} \n } `;
        }
        return result;
      }
      case 'UnaryExpression': {
        let operator = ast.operator;
        let argument = generateCpp(ast.argument);
        if (operator === "typeof")
          return `typeid(${argument}).name()`

        return `${operator}${argument} `;
      }
      case 'AssignmentExpression': {
        return `${generateCpp(ast.left)} ${ast.operator} ${generateCpp(ast.right)} `;
      }
      case 'ObjectExpression': {
        let properties = ast.properties.map(property => {
          let key = generateCpp(property.key);
          let value = generateCpp(property.value);
          return `{${key}, ${value} } `;
        }).join(', ');
        return `std:: map < std:: string, ${valueType(ast.properties[0].value)}> { ${properties}
  } `;
      }
      case 'Property':
        return `${generateCpp(ast.key)}: ${generateCpp(ast.value)} `;
      case 'ArrayExpression': {
        let elements = ast.elements.map(generateCpp).join(', ');
        return `JSArray(${elements})`;
      }
      case 'EmptyStatement': {
        return ';';
      }
      case 'ExpressionStatement': {
        if (ast.expression.type === 'CallExpression' && ast.expression.callee.type === 'MemberExpression' && ast.expression.callee.object.name === 'console') {
          let args = ast.expression.arguments.map(generateCpp).join(' << ');
          let typeOfCout = "cout"
          if (ast.expression.callee.property.name === 'error')
            typeOfCout = "cerr"
          return `std::${typeOfCout} << ${args}.toString() << std:: endl; `;
        } else {
          return generateCpp(ast.expression) + ';';
        }
      }
      case 'ForStatement': {
        let init = generateCpp(ast.init);
        let test = generateCpp(ast.test);
        let update = generateCpp(ast.update);
        let body = generateCpp(ast.body);
        return `for (${init} ${test}; ${update}) { \n${body} \n } `;
      }
      case 'WhileStatement':
        return `while (${generateCpp(ast.test)}) { \n${generateCpp(ast.body)} } \n`;
      case 'DoWhileStatement':
        return `do { \n${generateCpp(ast.body)} } while (${generateCpp(ast.test)}); \n`;
      case 'UpdateExpression': {
        let operator = ast.operator === '++' ? '++' : '--';
        let argument = generateCpp(ast.argument);
        return `${argument}${operator} `;
      }
      case 'LogicalExpression': {
        let left = generateCpp(ast.left);
        let right = generateCpp(ast.right);
        let operator = ast.operator === '&&' ? '&&' : '||';
        return `(${left} ${operator} ${right})`;
      }
      case 'ConditionalExpression': {
        let test = generateCpp(ast.test);
        let consequent = generateCpp(ast.consequent);
        let alternate = generateCpp(ast.alternate);
        return `(${test} ? ${consequent} : ${alternate})`;
      }
      case 'SwitchStatement': {
        const test = generateCpp(ast.discriminant);
        const cases = ast.cases.map(c => generateCpp(c)).join('\n');
        return `switch (${test}) { \n${cases} } \n`;
      }
      case 'SwitchCase': {
        if (ast.test) {
          const test = generateCpp(ast.test);
          const consequent = ast.consequent.map(c => generateCpp(c)).join('\n');
          return `case ${test}: \n${consequent} `;
        } else {
          const consequent = ast.consequent.map(c => generateCpp(c)).join('\n');
          return `default: \n${consequent} `;
        }
      }
      case 'BreakStatement':
        return 'break;\n';
      case 'ContinueStatement':
        return 'continue;\n';
      case 'ThisExpression':
        return 'this';
      case 'NewExpression': {
        const callee = generateCpp(ast.callee);
        const args = ast.arguments.map(a => generateCpp(a)).join(', ');
        return `new ${callee} (${args})`;
      }
      case 'ThrowStatement': {
        const argument = generateCpp(ast.argument);
        return `throw ${argument}; \n`;
      }
      case 'TryStatement': {
        const block = generateCpp(ast.block);
        const handler = ast.handler
          ? `catch (${generateCpp(ast.handler.param)}) { \n${generateCpp(ast.handler.body)} } \n`
          : '';
        const finalizer = ast.finalizer ? `finally { \n${generateCpp(ast.finalizer)} } \n` : '';
        return `try { \n${block} } ${handler}${finalizer} `;
      }
      case 'CatchClause': {
        const param = generateCpp(ast.param);
        const body = generateCpp(ast.body);
        return `catch (${param}) { \n${body} } \n`;
      }
      case 'SpreadElement': {
        const argument = generateCpp(ast.argument);
        return `std:: copy(${argument}.begin(), ${argument}.end(), std:: back_inserter(${argument}_vector)); \n`;
      }
      case 'RestElement': {
        const argName = generateCpp(ast.argument);
        const paramName = argName.startsWith('&') ? argName.substring(1) : argName;
        return `std:: vector < ${getCppType(ast.argument.elements[0].type)}> ${paramName} _vector(${argName}); \n`;
      }
      default:
        console.log(`Unsupported AST node type: ${ast.type} `);
    }
  }


  return cppCode
}

module.exports = { generateWholeCode }