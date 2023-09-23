console.log("Number.EPSILON:", Math.floor(Number.EPSILON))
// console.log("Number.MAX_VALUE:", Number.MAX_VALUE)
// console.log("Number.MIN_VALUE:", Number.MIN_VALUE)
console.log("Number.NaN:", isNaN(Number.NaN))
// console.log("Number.NEGATIVE_INFINITY:", Number.NEGATIVE_INFINITY)
// console.log("Number.POSITIVE_INFINITY:", Number.POSITIVE_INFINITY)
// console.log("Number.MAX_SAFE_INTEGER:", Number.MAX_SAFE_INTEGER)
// console.log("Number.MIN_SAFE_INTEGER:", Number.MIN_SAFE_INTEGER)

console.log("Number.parseFloat:", Number.parseFloat("3.14"))
console.log("Number.parseInt:", Number.parseInt("42"))

// console.log("Number.isFinite:", Number.isFinite(42))
console.log("Number.isInteger:", Number.isInteger(42))
console.log("Number.isSafeInteger:", Number.isSafeInteger(42))

const num = new Number(42)
const num2 = Number(42)
console.log("Number.prototype.valueOf:", num.valueOf())
console.log("Number.prototype.toString:", num.toString())
console.log("Number.prototype.toPrecision:", num.toPrecision(4))
console.log("Number.prototype.toFixed:", num.toFixed(2))
