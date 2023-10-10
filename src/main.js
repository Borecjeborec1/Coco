const fs = require("fs");
const path = require("path");
const acorn = require("acorn");
const { tsPlugin } = require("acorn-typescript");

const {
    BUILTIN_JS_FUNCTIONS,
    DEFAULT_IMPORTS,
    IMPLEMENTED_JS_OBJECTS,
    ARRAY_DATA_TYPES,
    IMPLEMENTED_OBJECT_METHODS,
    ALLOWED_MODULES,
    OBJECTS_WITH_STATIC_GLOBAL_METHODS,
    TIMER_FUNCTIONS,
    ACCEPTED_ENDINGS_FOR_CC_LINKING,
} = require("./lib/JS/Builtin-Objects.js");
const {
    addAutoIfNotTypedAlready,
    isRegexString,
    getAllFiles,
    isModuleStatement,
    generateRandomString,
    mapUserType,
    addJSONIfNotTypedAlready,
} = require("./lib/JS/Helper-functions.js");

let config = {
    numberDataType: "int",
    outputBooleans: true,
    isModule: false,
    mockedRandom: true,
};

const userDefinedVariableNames = [];
const neededImports = [];

let linkedFilesContent = [];
let linkedFilesName = [];
let classVariablesDefinedByUser = [];

function generateWholeCode(ast, compilingOptions) {
    config = { ...config, ...compilingOptions };
    const mainBody = generateCpp(ast);
    return compilingOptions.isModule ? mainBody : joinCppParts(mainBody);
}

const storedConsoleTimeIds = {};

function handleCoutStatements(_methodName, _args, _id) {
    if (_methodName == "time") {
        const randomIdentifier = generateRandomString(6);
        storedConsoleTimeIds[randomIdentifier] = _id;
        return `auto ${randomIdentifier} = std::chrono::high_resolution_clock::now();`;
    }
    if (_methodName === "timeEnd") {
        let referedRandomIdentifier = getKeyByValue(storedConsoleTimeIds, _id);
        return `
std::cout << "${_id}: " << (std::chrono::duration_cast<std::chrono::milliseconds>(
std::chrono::high_resolution_clock::now() - ${referedRandomIdentifier})).count() << "ms" << std::endl;
`;
    }
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
            console.log("PARAMS? ", params);
            if (body.includes(`${funcName}(`))
                return `std::function<${config.numberDataType}(${config.numberDataType})> ${funcName} = [&](${params}) { \n${body} \n };`;

            return `auto ${funcName} = [](${params}) { \n${body} \n };`;
        }
        case "BlockStatement": {
            return ast.body.map(generateCpp).join("\n");
        }

        case "VariableDeclaration": {
            if (isModuleStatement(ast.declarations[0].init)) {
                const moduleName = ast.declarations[0].init.arguments[0].value;
                const variableName = ast.declarations[0].id.name;
                if (ALLOWED_MODULES[moduleName]) {
                    // Handle built-in node_modules
                    userDefinedVariableNames.push(variableName);
                    neededImports.push(moduleName + ".hh");
                    if (moduleName == "os")
                        newCppFlags += " -liphlpapi -lws2_32 ";
                    if (moduleName == "fs") newCppFlags += " -std=c++17 ";
                    return `using ${variableName} = ${ALLOWED_MODULES[moduleName]};`;
                }
                if (ast.declarations[0].id.type == "ObjectPattern") {
                    const randomObjectName = generateRandomString(6);
                    const destructured = ast.declarations[0].id.properties
                        .map((identifier) => {
                            const key = generateCpp(identifier.key);
                            const value = generateCpp(identifier.value);
                            return `auto ${value} = ${randomObjectName}::${key};`;
                        })
                        .join("\n");
                    linkNewJsFile(moduleName, randomObjectName);
                    return `${destructured}`;
                }
                linkNewJsFile(moduleName, variableName);
                return "";
            }

            if (ast.declarations[0].id.type === "ObjectPattern") {
                const randomObjectName = generateRandomString(6);
                const destructured = ast.declarations[0].id.properties
                    .map((property) => {
                        const key = generateCpp(property.key);
                        if (property.value.type == "AssignmentPattern") {
                            const value = generateCpp(property.value.left);
                            const defaultValue = generateCpp(
                                property.value.right
                            );
                            return `auto ${value} = ${randomObjectName}["${key}"] ||${defaultValue};`;
                        }
                        const value = generateCpp(property.value);
                        return `auto ${value} = ${randomObjectName}["${key}"];`;
                    })
                    .join("\n");
                const rhs = generateCpp(ast.declarations[0].init);
                return `auto ${randomObjectName} = ${rhs};\n ${destructured}`;
            }

            const declarations = ast.declarations.map(generateCpp).join(", ");
            const typeAnnotation = ast.declarations[0].id.typeAnnotation;
            const type = typeAnnotation
                ? generateCpp(typeAnnotation.typeAnnotation)
                : "";
            const declarationType = type ? "" : "auto"; //TODO: Handle const declaration

            return `${declarationType} ${declarations}; \n`;
        }
        case "VariableDeclarator": {
            if (ast.id.typeAnnotation)
                if (generateCpp(ast.id.typeAnnotation) && ast.init.raw)
                    return `${generateCpp(ast.id)} = ${ast.init.raw} `;

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
                case "undefined":
                    return "nlohmann::json()";
                case "null":
                    return "nlohmann::json()";
                case "NaN":
                    return "nlohmann::json()";
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
            } else if (typeof ast.value == "bigint") {
                return `static_cast<long long>(${ast.value})`;
            }
            return `nlohmann::json() // Unknown type: ${JSON.stringify(ast)}`;
        }

        case "BinaryExpression": {
            const lhs = generateCpp(ast.left);
            const rhs = generateCpp(ast.right);
            if (ast.operator === "%")
                return `(static_cast<int>(${lhs}) % static_cast<int>(${rhs}))`;
            if (ast.operator === "**") return `std::pow(${lhs}, ${rhs})`;
            if (ast.operator === "==") return `(${lhs} == ${rhs})`;
            if (ast.operator === "!=") return `(${lhs} != ${rhs})`;
            if (ast.operator === "===") return `(${lhs} == ${rhs})`;
            if (ast.operator === "!==") return `(${lhs} != ${rhs})`;

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
                        const coutType = ast.callee.property.name;
                        if (coutType === "time" || coutType === "timeEnd") {
                            const coutMethod =
                                ast.expression.callee.property.name;
                            const coutStringIdentifier =
                                ast.expression.arguments[0].value;
                            return handleCoutStatements(
                                coutMethod,
                                args,
                                coutStringIdentifier
                            );
                        }
                        if (coutType == "error")
                            return `std::cerr << ${args} << '\\n';`;
                        return `std::${typeOfCout} << ${args} << '\\n';`;
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
                } else if (constructorName === "BigInt") {
                    return `static_cast<long long>(${ast.arguments[0].raw})`;
                } else if (ARRAY_DATA_TYPES.includes(constructorName)) {
                    let idk = ast.arguments.map(generateCpp).join(", ");
                    return `nlohmann::json{${idk}}`;
                }
            }

            if (TIMER_FUNCTIONS.includes(ast.callee.name)) {
                isTimerUsed = true;
                neededImports.push("Timer.hh");
                return `__Timer__::${callee}(${ast.arguments
                    .map(generateCpp)
                    .join(", ")})`;
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

            return `[](${ast.params
                .map(generateCpp)
                .map((el) => "auto " + el)
                .join(", ")}) { return ${returnBody} } `;
        }
        case "MemberExpression": {
            const objectCode = generateCpp(ast.object);
            const propertyCode = ast.property.raw
                ? ast.property.raw
                : ast.property.name;
            if (propertyCode === "length") return `${objectCode}.length()`;
            if (propertyCode == "size") return `${objectCode}.size()`;
            if (objectCode == "this") return propertyCode;
            if (objectCode == "exports") return "// ";
            if (objectCode == "module") return "// ";
            if (propertyCode == "constructor") return `${objectCode}`;
            if (propertyCode == "prototype") return `${objectCode}`;
            if (userDefinedVariableNames.includes(objectCode))
                return `${objectCode}::${propertyCode}`;
            if (linkedFilesName.includes(objectCode))
                return `${objectCode}::${propertyCode}`;

            if (IMPLEMENTED_JS_OBJECTS[objectCode])
                return `${IMPLEMENTED_JS_OBJECTS[objectCode]}::${propertyCode}`;

            if (IMPLEMENTED_OBJECT_METHODS.includes(propertyCode))
                return `${objectCode}.${
                    propertyCode == "delete" ? "deleteKey" : propertyCode
                }`;
            if (classVariablesDefinedByUser.includes(propertyCode))
                return `${objectCode}.${propertyCode}`;
            return `${objectCode}[${propertyCode}]`;
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
                const coutType = ast.expression.callee.property.name;
                const args = ast.expression.arguments
                    .map(generateCpp)
                    .join(" << ");
                if (coutType == "time" || coutType == "timeEnd") {
                    const coutMethod = ast.expression.callee.property.name;
                    const coutStringIdentifier =
                        ast.expression.arguments[0].value;
                    return handleCoutStatements(
                        coutMethod,
                        args,
                        coutStringIdentifier
                    );
                }

                if (coutType === "error")
                    return `std::cerr << ${args} << '\\n';`;
                return `std::cout << ${args} << '\\n';`;
            } else {
                return generateCpp(ast.expression) + ";";
            }
        }
        case "ForStatement": {
            let init = generateCpp(ast.init);
            let test = generateCpp(ast.test);
            init = init.replace(
                `static_cast<${config.numberDataType}>`,
                "static_cast<long long int>"
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
        case "ChainExpression": {
            return generateCpp(ast.expression);
        }
        case "NewExpression": {
            const callee = generateCpp(ast.callee);
            const args = ast.arguments.map((a) => generateCpp(a)).join(", ");
            if (IMPLEMENTED_JS_OBJECTS[callee]) {
                if (callee == "Number")
                    return `static_cast<${config.numberDataType}>(${args})`;
                if (callee == "String") return `std::string(${args})`;
                if (callee == "BigInt")
                    return `static_cast<long long>(${ast.arguments[0].raw})`;
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
        case "SpreadElement": {
            const argument = generateCpp(ast.argument);
            return `__spreadOperator__(${argument})`;
        }
        case "AwaitExpression": {
            return generateCpp(ast.argument);
        }
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
            let greaterLoopI =
                expressions.length > quasis.length
                    ? expressions.length
                    : quasis.length;
            for (let i = 0; i < greaterLoopI; i++) {
                if (quasis[i]) result += `${quasis[i]},  `;
                if (expressions[i]) result += `${expressions[i]},  `;
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
        case "ImportDeclaration": {
            const importPath = ast.source.value;

            if (ast.specifiers[0].type == "ImportSpecifier") {
                const randomObjectName = generateRandomString(6);
                const destructured = ast.specifiers
                    .map((identifier) => {
                        const key = generateCpp(identifier.imported);
                        const value = generateCpp(identifier.local);
                        return `auto ${value} = ${randomObjectName}::${key};`;
                    })
                    .join("\n");
                linkNewJsFile(importPath, randomObjectName);
                return `${destructured}`;
            }

            const variableName = generateCpp(ast.specifiers[0].local);
            linkNewJsFile(importPath, variableName);
            return ``;
        }
        // case "ImportSpecifier":
        // case "ImportDefaultSpecifier":

        case "ClassDeclaration": {
            const className = ast.id.name;
            const classBody = ast.body.body;
            const constructorMethod = classBody.filter(
                (method) => method.kind == "constructor"
            )[0];
            const nonConstructorMethods = classBody.filter(
                (method) => method.kind != "constructor"
            );
            const classMethods = nonConstructorMethods
                .map(generateCpp)
                .join("\n");
            const classContructor = generateCpp(constructorMethod);
            const variableNamesMatched =
                classContructor.match(/([a-zA-Z_]\w*)\s*=/g) || [];

            const variableNames = variableNamesMatched.map((match) =>
                match.replace(/\s*=/, "").trim()
            );

            const typedVariables = variableNames
                .map((v) => "nlohmann::json " + v + ";")
                .join("\n");
            const methodNames = nonConstructorMethods.map(
                (node) => node.key.name
            );

            classVariablesDefinedByUser.push(...variableNames, ...methodNames);
            return `class ${className} {
                public:
                ${typedVariables}
                ${className}(){
                    ${classContructor}
                }
                ${classMethods}
                };`;
        }

        case "MethodDefinition": {
            const methodName = ast.key.name;
            const methodParams = ast.value.params
                .map(generateCpp)
                .map(addJSONIfNotTypedAlready)
                .join(", ");
            const methodBody = generateCpp(ast.value.body);
            if (ast.kind == "constructor") return methodBody;

            return `nlohmann::json ${methodName}(${methodParams}) {\n${methodBody}\n}`;
        }

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
let isTimerUsed = false;
function joinCppParts(mainBody = "") {
    const coutModifier = config.outputBooleans
        ? "std::cout.setf(std::ios::boolalpha);"
        : "";
    const randomNumberModifier = config.mockedRandom
        ? "srand ( time(NULL) );"
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
    const continousLoop = isTimerUsed
        ? `  while (!__Timer__::shouldExit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      };
    `
        : "";

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


  ${continousLoop}
  return 0;
}  
`;
}

function linkNewJsFile(fileName, namespaceName) {
    if (!fs.existsSync(path.join(path.dirname(config.cppFile), fileName)))
        return;

    const linkedFilePath = path.join(path.dirname(config.cppFile), fileName);
    let linkedContent = fs.readFileSync(linkedFilePath, "utf-8");
    if (
        !ACCEPTED_ENDINGS_FOR_CC_LINKING.some((ending) =>
            fileName.toLowerCase().endsWith(ending)
        )
    ) {
        const linkedAst = acorn.Parser.extend(tsPlugin()).parse(linkedContent, {
            sourceType: "module",
            ecmaVersion: "latest",
            locations: true,
        });
        linkedContent = generateWholeCode(linkedAst, {
            isModule: true,
        });
    }
    linkedFilesContent.push(linkedContent + "\n");
    linkedFilesName.push(namespaceName);
}

let newCppFlags = "";

function getCppFlags() {
    return newCppFlags;
}
module.exports = {
    generateWholeCode,
    generateCpp,
    generateRandomString,
    getCppFlags,
};

function getKeyByValue(object, value) {
    return Object.keys(object).find((key) => object[key] === value);
}
