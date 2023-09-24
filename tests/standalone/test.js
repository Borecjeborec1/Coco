const myPath = require("path")

// // Path Module Properties
// console.log("path.sep:", path.sep)
// console.log("path.delimiter:", path.delimiter)

// // Path Module Methods
// console.log(
//     "path.normalize:",
//     path.normalize("/test/user//folder1/../folder2/file.txt")
// )
console.log(
    "path.join:",
    myPath.join("/test", "user", "folder1", "..", "folder2", "file.txt")
)
// console.log(
//     "path.resolve:",
//     path.resolve("test/user", "folder1", "..", "folder2", "file.txt")
// )
// console.log("path.isAbsolute('/test/user'): ", path.isAbsolute("/test/user"))
// console.log(
//     "path.isAbsolute('folder1/../folder2/file.txt'): ",
//     path.isAbsolute("folder1/../folder2/file.txt")
// )

// console.log(
//     "path.relative:",
//     path.relative("/test/user/folder1", "/test/user/folder2")
// )
// console.log("path.dirname:", path.dirname("/test/user/folder1/file.txt"))
// console.log("path.basename:", path.basename("/test/user/folder1/file.txt"))
// console.log("path.extname:", path.extname("/test/user/folder1/file.txt"))

// console.log("path.parse:", path.parse("/test/user/folder1/file.txt"))
// console.log(
//     "path.format:",
//     path.format({ dir: "/test/user", base: "file.txt" })
// )

// // Example: Resolving Relative Paths
// console.log(
//     "Resolved Path:",
//     path.resolve("./test", "user", "folder1", "..", "folder2", "file.txt")
// )

// // Example: Joining Paths
// console.log("Joined Path:", path.join(__dirname, "folder1", "file.txt"))

// // Example: Getting the File Extension
// console.log("File Extension:", path.extname("script.js"))

// // Example: Parsing a Path
// const parsedPath = path.parse("/test/user/folder1/file.txt")
// console.log("Parsed Path:", parsedPath)
// console.log("Parsed Path Name:", parsedPath.name)

// // Example: Formatting a Path
// const formattedPath = path.format({
//     root: "/",
//     dir: "/test/user",
//     base: "file.txt",
//     ext: ".txt",
//     name: "file",
// })
// console.log("Formatted Path:", formattedPath)
