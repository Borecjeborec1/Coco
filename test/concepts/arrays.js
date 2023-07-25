const arr = [1, 2, 3, 4, 5];

const doubled = arr.map(x => x * 2);
console.log(doubled);

const filtered = arr.filter(x => x % 2 === 0);
console.log(filtered);

const sum = arr.reduce((acc, curr) => acc + curr, 0);
console.log(sum);

const index = arr.indexOf(3);
console.log(index);

arr.push(6);
console.log(arr);

arr.pop();
console.log(arr);