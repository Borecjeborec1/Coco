console.time("speedTest");
let sum = 0;
for (let i = 0; i < 10000000002; ++i) {
    sum += (i * i) / i;
}

console.log(sum);

console.timeEnd("speedTest");
