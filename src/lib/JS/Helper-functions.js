const fs = require("fs");
const path = require("path");
const { VALID_USER_TYPES } = require("./Builtin-Objects.js");
function addAutoIfNotTypedAlready(variable) {
    return variable.length === 1 ? "auto " + variable : variable;
}

function addJSONIfNotTypedAlready(variable) {
    return variable.length === 1 ? "nlohmann::json " + variable : variable;
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
function isModuleStatement(init) {
    return (
        init.type === "CallExpression" &&
        init.callee.type === "Identifier" &&
        init.callee.name === "require" &&
        init.arguments.length === 1 &&
        init.arguments[0].type === "Literal"
    );
}
function generateRandomString(length) {
    const charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    let randomString = "";

    for (let i = 0; i < length; i++) {
        const randomIndex = Math.floor(Math.random() * charset.length);
        randomString += charset.charAt(randomIndex);
    }

    return randomString;
}

function mapUserType(type) {
    return VALID_USER_TYPES[type];
}

module.exports = {
    addAutoIfNotTypedAlready,
    isRegexString,
    getAllFiles,
    isModuleStatement,
    generateRandomString,
    mapUserType,
    addJSONIfNotTypedAlready,
};
