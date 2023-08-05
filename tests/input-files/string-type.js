// Assuming JSString class and its methods are defined properly

const str = "Hello, world!";

console.log("Original String:", str.toString());
console.log("Length:", str.length);

console.log("Slice:", str.slice(0, 5).toString()); // Output: "Hello"
console.log("Substring:", str.substring(7, 12).toString()); // Output: "world"
console.log("Substr:", str.substr(7, 5).toString()); // Output: "world"

console.log("Replace:", str.replace("world", "Universe").toString()); // Output: "Hello, Universe!"
console.log("ReplaceAll:", str.replaceAll("l", "L").toString()); // Output: "HeLLo, worLd!"

console.log("ToUpperCase:", str.toUpperCase()); // Output: "HELLO, WORLD!"
console.log("ToLowerCase:", str.toLowerCase()); // Output: "hello, world!"

const otherString = " Welcome";
console.log("Concat:", str.concat(otherString).toString()); // Output: "Hello, world! Welcome"

const stringWithSpaces = "   Hello!   ";
console.log("Trim:", stringWithSpaces.trim().toString()); // Output: "Hello!"

const stringWithSpacesStart = "   Hello!";
console.log("TrimStart:", stringWithSpacesStart.trimStart().toString()); // Output: "Hello!"

const stringWithSpacesEnd = "Hello!   ";
console.log("TrimEnd:", stringWithSpacesEnd.trimEnd().toString()); // Output: "Hello!"

console.log("CharAt:", str.charAt(4).toString()); // Output: "o"
console.log("CharCodeAt:", str.charCodeAt(4).valueOf()); // Output: 111

console.log("Includes:", str.includes("world")); // Output: true
console.log("StartsWith:", str.startsWith("Hello")); // Output: true
console.log("EndsWith:", str.endsWith("world!")); // Output: true

console.log("Split:", str.split(",").toString()); // Output: ["Hello", " world!"]

console.log("IndexOf:", str.indexOf("o").valueOf()); // Output: 4
console.log("LastIndexOf:", str.lastIndexOf("o").valueOf()); // Output: 8

console.log("PadStart:", str.padStart(15, "*").toString()); // Output: "****Hello, world!"
console.log("PadEnd:", str.padEnd(15, "*").toString()); // Output: "Hello, world!****"

const regExp = "\\b\\w+\\b";
console.log("Match:", str.match(regExp).toString()); // Output: ["Hello", "world"]

const regExpSearch = "world";
console.log("Search:", str.search(regExpSearch).valueOf()); // Output: 7
