const fs = require("fs");
const path = require("path");
const acorn = require("acorn");
const { tsPlugin } = require("acorn-typescript");

const { BUILTIN_JS_FUNCTIONS } = require("./lib/JS/Builtin-functions.js");
const VALID_USER_TYPES = {
    int: "int",
    lint: "long int",
    llint: "long long int",
    uint: "unsigned",
    luint: "long unsigned",
    lluint: "long long unsigned",
    float: "double",
    double: "double",
    string: "std::string",
    void: "void",
    json: "nlohman::json",
    boolean: "bool",
};

const IMPLEMENTED_JS_OBJECTS = {
    JSON: "__JSON__",
    Math: "__Math__",
    Number: "__Number__",
    Date: "__Date__",
    String: "__String__",
    Boolean: "__Boolean__",
    Array: "__Array__",
};

const ARRAY_DATA_TYPES = [
    "Array",
    "Int8Array",
    "Uint8Array",
    "Uint8ClampedArray",
    "Int16Array",
    "Uint16Array",
    "Int32Array",
    "Uint32Array",
    "BigInt64Array",
    "BigUint64Array",
    "Float32Array",
    "Float64Array",
];

const IMPLEMENTED_DATE_METHODS = [
    "toISOString",
    "toString",
    "toDateString",
    "toTimeString",
    "toJSON",
    "getDate",
    "getDay",
    "getFullYear",
    "getHours",
    "getMilliseconds",
    "getMinutes",
    "getMonth",
    "getSeconds",
    "getTime",
    "getTimezoneOffset",
    "setFullYear",
    "setMonth",
    "setDate",
    "setHours",
    "setMinutes",
    "setSeconds",
    "setMilliseconds",
    "toUTCString",
    "toLocaleString",
    "toLocaleDateString",
    "toLocaleTimeString",
];

const ALLOWED_MODULES = {
    path: "__path__",
    os: "__os__",
    fs: "__fs__",
};

const OBJECTS_WITH_STATIC_GLOBAL_METHODS = ["Date", "Array"]; // Array holding names that have static methods, that are also global, and custom user variable names for node modules
const userDefinedVariableNames = [];
const DEFAULT_IMPORTS = [
    "nlohmann-json.hh",
    "Global-functions.hh",
    "Array-methods.hh",
    "Boolean-methods.hh",
    "String-methods.hh",
    "Number-methods.hh",
    "json-operators.hh",
    "string-operators.hh",
    "Array.hh",
    "Bool.hh",
    "Date.hh",
    "JSON.hh",
    "Math.hh",
    "Number.hh",
    "String.hh",
];
const neededImports = [];
let config = { numberDataType: "int", outputBooleans: true, isModule: false };
function generateWholeCode(ast, compilingOptions) {
    config = { ...config, ...compilingOptions };
    const mainBody = generateCpp(ast);
    return compilingOptions.isModule ? mainBody : joinCppParts(mainBody);
}

let linkedFilesContent = [];
let linkedFilesName = [];

function mapUserType(type) {
    return VALID_USER_TYPES[type];
}

function addAutoType(variable) {
    return "auto " + variable;
}

function needAutoType(variable) {
    return variable.length === 1;
}

function addAutoIfNotTypedAlready(variable) {
    return needAutoType(variable) ? addAutoType(variable) : variable;
}

function isRegexString(value) {
    const regexPattern = /^\/((?!\/).)+\/[gimsu]*$/;
    return typeof value === "string" && regexPattern.test(value);
}

function getAllFiles(dir, fileList = []) {
    const files = fs.readdirSync(dir);

    files.forEach((file) => {
        const filePath = path.join(dir, file);
        if (fs.statSync(filePath).isDirectory()) {
            getAllFiles(filePath, fileList);
        } else {
            fileList.push(filePath);
        }
    });

    return fileList;
}

function generateCpp(ast, compilingOptions) {
    if (compilingOptions) config = { ...config, ...compilingOptions };
    try {
        // console.log("Translating:: " + ast.type)
        let x = ast.type;
    } catch (er) {
        console.log("er no type: " + er);
        return "";
    }
    switch (ast.type) {
        case "Program":
            return ast.body.map(generateCpp).join("\n");
        case "FunctionDeclaration": {
            const funcName = generateCpp(ast.id);
            const params = ast.params
                .map(generateCpp)
                .map(addAutoIfNotTypedAlready)
                .join(", ");
            const body = generateCpp(ast.body);
            return `auto ${funcName} = [](${params}) { \n${body} \n };`;
        }
        case "BlockStatement": {
            return ast.body.map(generateCpp).join("\n");
        }
        case "VariableDeclaration": {
            const declarations = ast.declarations.map(generateCpp).join(", ");
            const typeAnnotation = ast.declarations[0].id.typeAnnotation;
            const type = typeAnnotation
                ? generateCpp(typeAnnotation.typeAnnotation)
                : "";
            const declarationType = type ? "" : "auto"; //TODO: Handle const declaration
            if (
                ast.declarations[0].init.type === "CallExpression" &&
                ast.declarations[0].init.callee.type === "Identifier" &&
                ast.declarations[0].init.callee.name === "require" &&
                ast.declarations[0].init.arguments.length === 1 &&
                ast.declarations[0].init.arguments[0].type === "Literal"
            ) {
                const moduleName = ast.declarations[0].init.arguments[0].value;
                const variableName = ast.declarations[0].id.name;
                if (ALLOWED_MODULES[moduleName]) {
                    userDefinedVariableNames.push(variableName);
                    neededImports.push(variableName);
                    return `using ${variableName} = ${ALLOWED_MODULES[moduleName]};`;
                }
                if (
                    !fs.existsSync(
                        path.join(path.dirname(config.cppFile), moduleName)
                    )
                ) {
                    return "";
                }
                const linkedFilePath = path.join(
                    path.dirname(config.cppFile),
                    moduleName
                );
                const linkedContent = fs.readFileSync(linkedFilePath, "utf-8");
                const linkedAst = acorn.Parser.extend(tsPlugin()).parse(
                    linkedContent,
                    {
                        sourceType: "module",
                        ecmaVersion: "latest",
                        locations: true,
                    }
                );
                const linkedFileContent = generateWholeCode(linkedAst, {
                    isModule: true,
                });
                linkedFilesContent.push(linkedFileContent + "\n");
                linkedFilesName.push(variableName);
                return "";
            }

            return `${declarationType} ${declarations}; \n`;
        }
        case "VariableDeclarator": {
            if (generateCpp(ast.id.typeAnnotation) && ast.init.raw) {
                return `${generateCpp(ast.id)} = ${ast.init.raw} `;
            }
            return `${generateCpp(ast.id)} = ${generateCpp(ast.init)} `;
        }
        case "Identifier": {
            if (ast.typeAnnotation) {
                return `${generateCpp(ast.typeAnnotation)} ${ast.name} `;
            }
            switch (ast.name) {
                case "__dirname":
                    return `"${__dirname}"`;
                case "__filename":
                    return `"${__filename}"`;
                default:
                    return ast.name;
            }
        }
        case "Literal": {
            if (ast.typeAnnotation) {
                return ast.value.toString();
            }
            if (isRegexString(ast.value)) {
                const [, pattern, flags] = ast.value
                    .toString()
                    .match(/\/(.+)\/([a-z]*)/);
                let regexFlags = "std::regex::ECMAScript";
                if (flags.includes("i")) regexFlags += " | std::regex::icase";
                if (flags.includes("m"))
                    regexFlags += " | std::regex::multiline";
                if (flags.includes("s")) regexFlags += " | std::regex::dotall";
                if (flags.includes("x"))
                    regexFlags += " | std::regex::extended";
                if (flags.includes("U"))
                    regexFlags += " | std::regex::ungreedy";

                return `std::regex("${pattern}", ${regexFlags})`;
            }
            if (typeof ast.value === "string") {
                return `std::string("${ast.value}")`;
            } else if (typeof ast.value === "number") {
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
                return `(${generateCpp(ast.left)} == ${generateCpp(
                    ast.right
                )})`;
            } else if (ast.operator === "!==")
                return `(${generateCpp(ast.left)} != ${generateCpp(
                    ast.right
                )})`;

            return `(${generateCpp(ast.left)} ${ast.operator} ${generateCpp(
                ast.right
            )})`;
        }
        case "ReturnStatement":
            return `return ${generateCpp(ast.argument)}; `;
        case "CallExpression": {
            const callee = generateCpp(ast.callee);

            if (
                ast.callee.type === "MemberExpression" &&
                ast.callee.property &&
                ast.callee.object
            ) {
                if (ast.callee.object.name === "console") {
                    if (
                        ast.type === "CallExpression" &&
                        ast.callee.type === "MemberExpression" &&
                        ast.callee.object.name === "console"
                    ) {
                        let args = ast.arguments.map(generateCpp).join(" << ");
                        let typeOfCout =
                            ast.callee.property.name === "error"
                                ? "cerr"
                                : "cout";
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
                let variableName =
                    ast.callee.object.name || generateCpp(ast.callee.object); // Ensure that nested methods get called right
                if (
                    jsFunction &&
                    !userDefinedVariableNames.includes(variableName)
                ) {
                    const { name, argCount } = jsFunction;
                    if (ast.arguments && ast.arguments.length > 0) {
                        const args = ast.arguments
                            .slice(0, argCount)
                            .map(generateCpp)
                            .join(", ");
                        if (
                            OBJECTS_WITH_STATIC_GLOBAL_METHODS.includes(
                                variableName
                            )
                        )
                            return `${name}(${args})`;

                        return `${name}(${variableName}, ${args})`;
                    } else {
                        return `${name}(${variableName})`;
                    }
                }
            }

            if (ast.callee.type === "Identifier") {
                const constructorName = ast.callee.name;
                if (constructorName === "Boolean") {
                    return `JS_CAST_ExclamationBoolean(JS_CAST_ExclamationBoolean(${generateCpp(
                        ast.arguments[0]
                    )}))`;
                } else if (constructorName === "String") {
                    return `std::string(${generateCpp(ast.arguments[0])})`;
                } else if (constructorName === "Number") {
                    return `static_cast<${config.numberDataType}>(${generateCpp(
                        ast.arguments[0]
                    )})`;
                } else if (ARRAY_DATA_TYPES.includes(constructorName)) {
                    let idk = ast.arguments.map(generateCpp).join(", ");
                    return `nlohmann::json{${idk}}`;
                }
            }
            return `${callee}(${ast.arguments.map(generateCpp).join(", ")})`;
        }
        case "FunctionExpression":
            return `[](${ast.params
                .map(generateCpp)
                .map((el) => "auto " + el)
                .join(", ")}) { \n${generateCpp(ast.body)} \n } `;
        case "ArrowFunctionExpression": {
            if (ast.body.type === "BlockStatement")
                return `[](${ast.params
                    .map(generateCpp)
                    .map((el) => "auto " + el)
                    .join(", ")}) { \n${generateCpp(ast.body)} \n } `;

            const returnBody = generateCpp(ast.body);
            const returnString = returnBody.includes("return;")
                ? `${returnBody}`
                : `return ${returnBody};`;

            return `[](${ast.params
                .map(generateCpp)
                .map((el) => "auto " + el)
                .join(", ")}) { ${returnString} } `;
        }
        case "MemberExpression": {
            const objectCode = generateCpp(ast.object);
            const propertyCode = ast.property.name;
            if (propertyCode === "length") return `${objectCode}.length()`;
            if (objectCode == "this") return propertyCode;
            if (objectCode == "exports") return "auto " + propertyCode;
            if (userDefinedVariableNames.includes(objectCode))
                return `${objectCode}::${propertyCode}`;
            if (linkedFilesName.includes(objectCode)) {
                return `${objectCode}::${propertyCode}`;
            }
            if (IMPLEMENTED_JS_OBJECTS[objectCode])
                return `${IMPLEMENTED_JS_OBJECTS[objectCode]}::${propertyCode}`;

            if (IMPLEMENTED_DATE_METHODS.includes(propertyCode))
                return `${objectCode}.${propertyCode}`;
            return `${objectCode}["${propertyCode}"]`;
        }
        case "IfStatement": {
            let result = `if (${generateCpp(ast.test)}) {\n${generateCpp(
                ast.consequent
            )}\n}`;
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
            } else if (operator === "!") {
                return `JS_CAST_ExclamationBoolean(${argument})`;
            }
            return `${operator}${argument} `;
        }
        case "AssignmentExpression": {
            if (ast.operator === "+=")
                return `${generateCpp(ast.left)} = ${generateCpp(
                    ast.left
                )} + ${generateCpp(ast.right)}`;
            return `${generateCpp(ast.left)} ${ast.operator} ${generateCpp(
                ast.right
            )}`;
        }
        case "ObjectExpression": {
            let properties = ast.properties
                .map(
                    (property) =>
                        `{"${generateCpp(property.key)}", ${generateCpp(
                            property.value
                        )}}`
                )
                .join(", ");
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
            if (
                ast.expression.type === "CallExpression" &&
                ast.expression.callee.type === "MemberExpression" &&
                ast.expression.callee.object.name === "console"
            ) {
                let args = ast.expression.arguments
                    .map(generateCpp)
                    .join(" << ");
                let typeOfCout = "cout";
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
                    typeOfCout = "cerr";
                }
                return `std::${typeOfCout} << ${args} << '\\n';`;
            } else {
                return generateCpp(ast.expression) + ";";
            }
        }
        case "ForStatement": {
            let init = generateCpp(ast.init).replace(
                `static_cast<${config.numberDataType}>`,
                "static_cast<long long>"
            );
            let test = generateCpp(ast.test).replace(
                `static_cast<${config.numberDataType}>`,
                "static_cast<long long>"
            );
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
            if (ast.left.declarations[0].id.elements) {
                // array of keys inside loop
                const index = ast.left.declarations[0].id.elements[0].name;
                const value = ast.left.declarations[0].id.elements[1].name;
                return `
        int ${index} = 0;
        for (const auto&  __val__ : ${right}) {
          auto ${value} = __val__[1];
          ${body}
          ${index}= ${index} + 1;
        }`;
            }
            const left = generateCpp(ast.left.declarations[0].id);
            return `for (const auto& ${left} : ${right}) {
        ${body}
      }`;
        }
        case "WhileStatement":
            return `while (${generateCpp(ast.test)}) { \n${generateCpp(
                ast.body
            )} } \n`;
        case "DoWhileStatement":
            return `do { \n${generateCpp(ast.body)} } while (${generateCpp(
                ast.test
            )}); \n`;
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
            const cases = ast.cases.map((c) => generateCpp(c)).join("\n");
            return `switch (${test}) { \n${cases} } \n`;
        }
        case "SwitchCase": {
            if (ast.test) {
                const test = generateCpp(ast.test);
                const consequent = ast.consequent
                    .map((c) => generateCpp(c))
                    .join("\n");
                return `case ${test}: \n${consequent} `;
            } else {
                const consequent = ast.consequent
                    .map((c) => generateCpp(c))
                    .join("\n");
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
            const args = ast.arguments.map((a) => generateCpp(a)).join(", ");
            if (IMPLEMENTED_JS_OBJECTS[callee]) {
                if (callee == "Number")
                    return `static_cast<${config.numberDataType}>(${args})`;
                if (callee == "String") return `std::string(${args})`;
                if (callee == "Boolean")
                    return `JS_CAST_ExclamationBoolean(JS_CAST_ExclamationBoolean(${args}))`;
                if (ARRAY_DATA_TYPES.includes(callee)) {
                    let idk = ast.arguments.map(generateCpp).join(", ");
                    return `nlohmann::json{${idk}}`;
                }
                return `${IMPLEMENTED_JS_OBJECTS[callee]} (${args})`;
            }
            return `${callee} (${args})`;
        }
        case "ThrowStatement": {
            const argument = generateCpp(ast.argument);
            return `throw ${argument}; \n`;
        }
        case "TryStatement": {
            const block = generateCpp(ast.block);
            const handler = ast.handler
                ? `catch (${generateCpp(ast.handler.param)}) { \n${generateCpp(
                      ast.handler.body
                  )} } \n`
                : "";
            const finalizer = ast.finalizer
                ? `finally { \n${generateCpp(ast.finalizer)} } \n`
                : "";
            return `try { \n${block} } ${handler}${finalizer} `;
        }
        case "CatchClause": {
            const param = generateCpp(ast.param);
            const body = generateCpp(ast.body);
            return `catch (${param}) { \n${body} } \n`;
        }
        // case "SpreadElement": {
        //     const argument = generateCpp(ast.argument);
        //     return `std:: copy(${argument}.begin(), ${argument}.end(), std:: back_inserter(${argument}_vector)); \n`;
        // }
        // case "RestElement": {
        //     const argName = generateCpp(ast.argument);
        //     const paramName = argName.startsWith("&")
        //         ? argName.substring(1)
        //         : argName;
        //     return;
        //     // return `std:: vector < ${getCppType(ast.argument.elements[0].type)}> ${paramName} _vector(${argName}); \n`;
        // }
        case "TemplateLiteral": {
            const quasis = ast.quasis.map(generateCpp);
            const expressions = ast.expressions.map((expression) =>
                generateCpp(expression)
            );
            let result = ``;

            for (let i = 0; i < expressions.length; i++) {
                result += `${quasis[i]},  `;
                result += `${expressions[i]},  `;
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
            return mapUserType(typeName) || "";
        }
        case "TSAnyKeyword": {
            return "auto ";
        }
        // case "ClassDeclaration": {
        //     const className = ast.id.name;
        //     const classBody = ast.body.body.map(generateCpp).join("\n");

        //     return `class ${className} {\n${classBody}\n};`;
        // }

        // case "MethodDefinition": {
        //     const methodName = ast.key.name;
        //     const methodParams = ast.value.params
        //         .map(generateCpp)
        //         .map(addAutoIfNotTypedAlready)
        //         .join(", ");
        //     const methodBody = generateCpp(ast.value.body);

        //     if (ast.kind === "constructor") {
        //         // // Constructor method
        //         // console.log(ast.parent);
        //         // return `${ast.parent.name}(${methodParams}) {\n${methodBody}\n}`;
        //     } else {
        //         // Regular method
        //         return `auto ${methodName}(${methodParams}) {\n${methodBody}\n}`;
        //     }
        // }

        // case "ImportDeclaration":
        //     // Extract the module specifier from the import statement
        //     const importPath = ast.source.value;

        //     // Resolve the file path to the actual file location
        //     const resolvedImportPath = resolveFilePath(importPath);
        //     console.log("IN IMPORT");
        //     // Generate the C++ #include statement using the .hh extension
        //     const includeStatement = `#include "${resolvedImportPath}.hh"`;

        //     return includeStatement;
        default:
            console.log(`Unsupported AST node type: ${ast.type} `);
    }
}

function joinCppParts(mainBody = "") {
    const coutModifier = config.outputBooleans
        ? "std::cout.setf(std::ios::boolalpha);"
        : "";
    const rootDirectory = "/lib/C++";

    const allFiles = getAllFiles(__dirname + rootDirectory);
    const includeStatements = allFiles

        .filter(
            (filePath) =>
                DEFAULT_IMPORTS.includes(path.basename(filePath)) ||
                neededImports.includes(path.basename(filePath))
        )
        .map((filePath) => {
            const libIndex = filePath.indexOf("lib");

            const extractedPath = filePath.substring(libIndex);
            return `#include "./${extractedPath
                .replace("C++\\", "")
                .replace(/\\/g, "/")}"`;
        })
        .join("\n");
    let externalNamespaces = "";
    for (let i = 0; i < linkedFilesContent.length; ++i) {
        externalNamespaces += `namespace ${linkedFilesName[i]} {
                ${linkedFilesContent[i]}
            };`;
    }
    return `

// All new includes goes here
#include <chrono>
#include <iostream>
${includeStatements}

${externalNamespaces}

// Main Function (Have to be the only main function)
int main(){
  ${coutModifier}
  ${mainBody}
  return 0;
}  
`;
}

module.exports = { generateWholeCode, generateCpp };
