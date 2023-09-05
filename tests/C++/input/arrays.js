let arr = [1, 2, 3, 5, 4];

console.log("concat:", arr.concat([6, 7]));
// console.log("copyWithin:", arr.copyWithin(0, 3));
// console.log("entries:");
// for (const [index, value] of arr.entries()) {
//   console.log(index, value);
// }
console.log("every:", arr.every(item => item > 0));
console.log("fill:", arr.fill(0, 2, 4));
console.log("filter:", arr.filter(item => item * 2 === 4));
console.log("find:", arr.find(item => item > 3));
console.log("findIndex:", arr.findIndex(item => item > 3));
// console.log("flat:", arr.flat());
// console.log("flatMap:", arr.flatMap(item => [item * 2, item * 3]));
console.log("forEach:");
// arr.forEach(item => console.log(item));
// console.log("includes:", arr.includes(3));
// console.log("indexOf:", arr.indexOf(3));
// console.log("isArray:", Array.isArray(arr));
// console.log("join:", arr.join(" - "));
// console.log("keys:");
// for (const key of arr.keys()) {
//   console.log(key);
// }
// console.log("lastIndexOf:", arr.lastIndexOf(3));
// console.log("map:", arr.map(item => item * 2));
// console.log("pop:", arr.pop());
// console.log("push:", arr.push(6));
// console.log("reduce:", arr.reduce((acc, item) => acc + item, 0));
// console.log("reduceRight:", arr.reduceRight((acc, item) => acc + item, 0));
// console.log("reverse:", arr.reverse());
// console.log("shift:", arr.shift());
// console.log("slice:", arr.slice(1, 3));
// console.log("some:", arr.some(item => item > 4));
// console.log("sort:", arr.sort());
// console.log("splice:", arr.splice(1, 2));
// console.log("toLocaleString:", arr.toLocaleString());
// console.log("toString:", arr.toString());
// console.log("unshift:", arr.unshift(0));
// console.log("values:");
// for (const value of arr.values()) {
//   console.log(value);
// }
