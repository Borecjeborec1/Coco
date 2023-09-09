let arr = [1, 2, 3, 5, 4];
console.log("entries:");
for (const [index, value] of arr.entries()) {
  console.log(index, value);
}

console.log("keys:");
for (const key of arr.keys()) {
  console.log(key);
}