const str = "Hello, World!";

// Character Access
console.log("charAt:", str.charAt(0));
console.log("charCodeAt:", str.charCodeAt(0));

// Case Conversion
console.log("toLowerCase:", str.toLowerCase());
console.log("toUpperCase:", str.toUpperCase());
console.log("toLocaleLowerCase:", str.toLocaleLowerCase());
console.log("toLocaleUpperCase:", str.toLocaleUpperCase());

// Concatenation
console.log("concat:", str.concat(" Welcome"));

// Searching and Matching
console.log("includes:", str.includes("World"));
console.log("startsWith:", str.startsWith("Hello"));
console.log("endsWith:", str.endsWith("World!"));
console.log("indexOf:", str.indexOf("o"));
console.log("lastIndexOf:", str.lastIndexOf("o"));
// console.log("match:", str.match("o")); // Match is working, but does not return the same type as in JS. Idk what to about that.
// console.log("match:", str.matchAll("o")); // Match is working, but does not return the same type as in JS. Idk what to about that.
// // [{groups:{},index:4,input:Hello, World!,match:o}] --> [ o, index: 4, input: Hello, World!, groups: undefined ]
console.log("search:", str.search("World"));

// Extraction
console.log("slice:", str.slice(7, 12));
console.log("substring:", str.substring(7, 12));
console.log("substr:", str.substr(7, 5));

// // Transformation
console.log("replace:", str.replace("World", "Universe"));
console.log("repeat:", str.repeat(2));
console.log("trim:", "   Hello, World!   ".trim());

// Splitting 
console.log("split:", str.split(","));

// Miscellaneous
console.log("length:", str.length);
console.log("valueOf:", str.valueOf());

// Unicode Manipulation
console.log("normalize:", "l\u0308".normalize()); // Unicode normalization
