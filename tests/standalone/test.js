const fs = require("fs");

// fs.readFile("./time.py", (er, data) => {
//     console.log("in readfile");
//     console.log(data);
// });

// let data = fs.readFileSync("./time.py", "utf-8");
// console.log(data);
// fs.writeFile("./time2.py", "data", (er) => {
//     console.log("in writefile");
// });

// fs.writeFileSync("./time2.py", "xDDDDDD");
// fs.access("./time2.py", (e) => {});
// // fs.chmodSync("./time2.py", 3); // Working but I dont want to change permisison with each test
// fs.appendFileSync("./time2.py", "test");
let idk = fs.readdirSync(".", {});
console.log(idk);
