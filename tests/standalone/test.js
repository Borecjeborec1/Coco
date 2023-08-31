const N = 1500;
let sum = 0;

console.time("Sum");
for (let i = 1; i <= N; i += 0.0000003) {
  sum += i * i;
}
console.timeEnd("Sum");

console.log("Sum:", sum);
