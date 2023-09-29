function returnxy(a, b) {
    return { x: a, y: b, c: 10 };
}

// let { x, y } = returnxy(1, 2);
const { x, ...rest } = returnxy(1, 2);

console.log(x, rest);
