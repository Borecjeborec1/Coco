const N = 1000000000;
let sum = 0;

console.time("Sum");
for (let i = 1; i <= N; ++i) {
  sum += i * i;
}
console.timeEnd("Sum");

console.log("Sum:", sum);
