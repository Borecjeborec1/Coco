function factorialRecursive(n) {
    if (n === 0) return 1;
    return n * factorialRecursive(n - 1);
}

function factorialIterative(n) {
    let result = 1;
    for (let i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

const numberToCalculate = 10000;

console.time("Recursive");
for (let i = 0; i < 100000; i++) {
    factorialRecursive(numberToCalculate);
}
console.timeEnd("Recursive");

console.time("Iterative");
for (let i = 0; i < 100000; i++) {
    factorialIterative(numberToCalculate);
}
console.timeEnd("Iterative");
