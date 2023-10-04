const fs = require("fs");
const inputString = fs.readFileSync("../../src/main.js");

// Define a regular expression pattern to match case statements
const regex = /case\s+"([^"]+)":\s*{/g;

// Create an array to store the matched case statements
const caseStatements = [];

// Use a loop to find and extract case statements
let match;
while ((match = regex.exec(inputString))) {
    const caseValue = match[1];
    caseStatements.push(caseValue);
}

// Now, caseStatements array contains the values of all case statements
console.log(caseStatements);
