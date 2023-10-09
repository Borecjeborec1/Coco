const iterations = 1e8; // 10^8

console.time("Nodejs");
let sum = 0;
for (let i = 1; i <= iterations; i++) {
    sum += i;
}

let x = 12;
let y = "12";
console.log(x == y);
console.log(x === y);
console.timeEnd("Nodejs");

console.log("Sum:", sum);
