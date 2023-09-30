console.log("HELLO WORLD!");
let x = setTimeout(() => console.log("setTimeout executed"), 2000);

let y = setImmediate(() => console.log("setImmidiate executed"));

let z = setInterval(() => {
    let count = 0;
    console.log("setInterval executed (" + count + ").");
    count++;
    if (count >= 5) {
    }
}, 1000);

console.log("test");
