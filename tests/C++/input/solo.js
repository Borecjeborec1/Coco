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
console.log("path.parse:", parsed.root);
console.log("path.parse:", parsed.dir);
console.log("path.parse:", parsed.base);
console.log("path.parse:", parsed.ext);
console.log("path.parse:", parsed.name);
let parsed2 = path.parse("test/user/folder1/file.txt");
console.log("path.parse:", parsed2.root);
console.log("path.parse:", parsed2.dir);
console.log("path.parse:", parsed2.base);
console.log("path.parse:", parsed2.ext);
console.log("path.parse:", parsed2.name);
let parsed3 = path.parse("C://test/user/folder1/file.txt");
console.log("path.parse:", parsed3.root);
console.log("path.parse:", parsed3.dir);
console.log("path.parse:", parsed3.base);
console.log("path.parse:", parsed3.ext);
console.log("path.parse:", parsed3.name);

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
