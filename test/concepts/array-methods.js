const nums = [1, 2, 3, 4, 5];

const sum = nums.reduce((acc, curr) => acc + curr, 0);
console.log(sum);

const filtered = nums.filter(x => x % 2 === 0);
console.log(filtered);

const mapped = nums.map(x => x * 2);
console.log(mapped);

const indexOf = nums.indexOf(3);
console.log(indexOf);

const joined = nums.join(', ');
console.log(joined);

const sliced = nums.slice(1, 4);
console.log(sliced);
