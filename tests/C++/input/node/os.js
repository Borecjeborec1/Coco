const os = require("os");

// OS Properties and Methods
console.log("os.EOL:", os.EOL);
console.log("os.arch:", os.arch());
console.log("os.freemem", os.freemem().toString().substring(0, 2));
console.log("os.homedir:", os.homedir());
console.log("os.hostname:", os.hostname().substring(0, 1));
console.log("os.machine():", os.machine());
console.log("os.platform:", os.platform());
// console.log("os.release:", os.release()); // Shows a bit different output than node
console.log("os.tmpdir:", os.tmpdir());
console.log("os.totalmem:", os.totalmem());
console.log("os.type:", os.type());
console.log("os.uptime:", os.uptime().toString().substring(0, 3));
// console.log("os.version:", os.version()); // Shows a bit different output than node
// console.log("os.networkInterfaces:", os.networkInterfaces()); // Working with new flags
// console.log("os.cpus:", os.cpus()); // Shows a bit different output than node
