const strObj = new String("Hello, World!");
const strObj2 = String("Hello, World!");

// console.log("String.prototype.constructor:", strObj.constructor);
console.log("String.prototype.length:", strObj.length);

console.log(
    "String.fromCharCode:",
    String.fromCharCode(72, 101, 108, 108, 111)
);
console.log(
    "String.fromCodePoint:",
    String.fromCodePoint(72, 101, 108, 108, 111)
);
