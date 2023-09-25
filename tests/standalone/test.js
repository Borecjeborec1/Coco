const fs = require("fs");

fs.readFile("./time.py", (er, data) => {
    console.log("ere");
    console.log(data);
});

let data = fs.readFileSync("./time.py", "utf-8");
console.log("HEYO");
console.log(data);
