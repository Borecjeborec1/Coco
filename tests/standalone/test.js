setTimeout(() => console.log("setTimeout executed"), 2000);

setImmediate(() => console.log("setImmidiate executed"));

setInterval(() => {
    let count = 0;
    console.log(("setInterval executed (" << count) << ").");
    count++;
    if (count >= 5) {
    }
}, 1000);

console.log("test");
