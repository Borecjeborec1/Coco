const path = require("path");

console.log("path.sep:", path.sep);
console.log("path.delimiter:", path.delimiter);

console.log("path.basename:", path.basename("/test/user/folder1/file.txt"));
console.log("path.dirname:", path.dirname("/test/user/folder1/file.txt"));
console.log("path.extname:", path.extname("/test/user/folder1/file.txt"));
console.log("Joined Path:", path.join("folder1", "file.txt"));
console.log("path.isAbsolute('/test/user'): ", path.isAbsolute("/test/user"));
console.log(
    "path.normalize:",
    path.normalize("/test/user//folder1/../folder2/file.txt")
);

let parsed = path.parse("/test/user/folder1/file.txt");
console.log("path.parse:", parsed.root.toString());
console.log("path.parse:", parsed.dir.toString());
console.log("path.parse:", parsed.base.toString());
console.log("path.parse:", parsed.ext.toString());
console.log("path.parse:", parsed.name.toString());
let parsed2 = path.parse("test/user/folder1/file.txt".toString());
console.log("path.parse:", parsed2.root.toString());
console.log("path.parse:", parsed2.dir.toString());
console.log("path.parse:", parsed2.base.toString());
console.log("path.parse:", parsed2.ext.toString());
console.log("path.parse:", parsed2.name.toString());
let parsed3 = path.parse("C://test/user/folder1/file.txt".toString());
console.log("path.parse:", parsed3.root.toString());
console.log("path.parse:", parsed3.dir.toString());
console.log("path.parse:", parsed3.base.toString());
console.log("path.parse:", parsed3.ext.toString());
console.log("path.parse:", parsed3.name.toString());

console.log(
    "path.relative:",
    path.relative("/test/user/folder1", "/test/user/folder2")
);

const formattedPath = path.format({
    root: "/",
    dir: "/test/user",
    base: "file.txt",
    ext: ".txt",
    name: "file",
});
console.log("Formatted Path:", formattedPath);
