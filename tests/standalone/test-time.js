let child = require("child_process").spawn("./test.exe", [], {
    cwd: process.cwd(),
    detached: true,
    stdio: "inherit",
});

child.stdout.on("data", console.log);
