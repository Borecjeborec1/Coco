const child_process = require("child_process");
child_process.exec("test.bat", [], (error, out, err) => {
    console.log("out", out);
});
