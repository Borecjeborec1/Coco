const IMPLEMENTED_JS_OBJECT_METHODS = [
    "toISOString",
    "toString",
    "toDateString",
]

const currentDate = new Date()

for (const method in currentDate.__prototype__) {
    console.log("HERE")
    if (
        typeof currentDate.__proto__[method] === "function" &&
        method !== "constructor"
    ) {
        IMPLEMENTED_JS_OBJECT_METHODS.push(method)
    }
}

console.log(IMPLEMENTED_JS_OBJECT_METHODS)
