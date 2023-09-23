const { expect, use } = require("chai")
const chaiString = require("chai-string")
const { generateCpp } = require("../../src/main") // Adjust the path accordingly
const acorn = require("acorn")

use(chaiString)

describe("generating variable types", function () {
    it("should convert let variables to C++ auto", function () {
        const jsCode = "let x = 42"
        const expectedCppCode = "auto x = static_cast<int>(42);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert var variables to C++ auto", function () {
        const jsCode = "var x = 42;"
        const expectedCppCode = "auto x = static_cast<int>(42);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert const variables to C++ auto", function () {
        const jsCode = "const x = 42;"
        const expectedCppCode = "auto x = static_cast<int>(42);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating data types", function () {
    it("should convert positive number C++ int", function () {
        const variableValue = 42
        const jsCode = `let x = ${variableValue};`
        const expectedCppCode = `auto x = static_cast<int>(${variableValue});`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert negative number C++ int", function () {
        const variableValue = -42
        const jsCode = `let x = ${variableValue};`
        const expectedCppCode = `auto x = static_cast<int>(0) - static_cast<int>(42);`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert string C++ std::string", function () {
        const variableValue = `"test-string"`
        const jsCode = `let x = ${variableValue};`
        const expectedCppCode = `auto x = std::string(${variableValue});`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert boolean C++ bool", function () {
        const variableValue = `true`
        const jsCode = `let x = ${variableValue};`
        const expectedCppCode = `auto x = ${variableValue};`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating objects and arrays", function () {
    it("should convert array C++ nlohmann::json", function () {
        const variableValue = `[12]`
        const jsCode = `let x = ${variableValue};`

        const expectedCppCode = `auto x = nlohmann::json{static_cast<int>(12)};`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert array with different data types to C++ nlohmann::json", function () {
        const variableValue = `[12, "test", true]`
        const jsCode = `let x = ${variableValue};`
        const expectedCppCode = `auto x = nlohmann::json{static_cast<int>(12), std::string("test"), true};`

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
    it("should convert object literal to C++ nlohmann::json", function () {
        const jsCode = 'let obj = { x: 12, y: "test", z: true };'
        const expectedCppCode =
            'auto obj = nlohmann::json{{"x", static_cast<int>(12)}, {"y", std::string("test")}, {"z", true}};'

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert nested object and array literal to C++ nlohmann::json", function () {
        const jsCode = "let data = { x: { y: [1, 2, 3] } };"
        const expectedCppCode =
            'auto data = nlohmann::json{{"x", nlohmann::json{{"y", nlohmann::json{static_cast<int>(1), static_cast<int>(2), static_cast<int>(3)}}}}};'

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating function", function () {
    describe("and declaring them", function () {
        it("should convert function declaration to C++ lambda", function () {
            const jsCode = "function add(a, b) { return a + b; }"
            const expectedCppCode =
                "auto add = [](auto a, auto b) { return (a + b); };"

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })

        it("should convert arrow function declaration without block to C++ lambda", function () {
            const jsCode = "const square = x => x * x;"
            const expectedCppCode =
                "auto square = [](auto x) { return (x * x); };"

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })

        it("should convert arrow function declaration with block to C++ lambda", function () {
            const jsCode = "const add = (a, b) => { return a + b; };"
            const expectedCppCode =
                "auto add = [](auto a, auto b) { return (a + b); };"

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })
    })

    describe("and calling them", function () {
        it("should convert function call to C++ lambda invocation", function () {
            const jsCode = "add(2, 3);"
            const expectedCppCode = `add(static_cast<int>(2), static_cast<int>(3));`

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })

        it("should convert arrow function call to C++ lambda invocation", function () {
            const jsCode = "const result = multiply(5, 3);"
            const expectedCppCode =
                "auto result = multiply(static_cast<int>(5), static_cast<int>(3));"

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })

        it("should handle nested function calls with different argument types", function () {
            const jsCode =
                "const result = calculate(add(2, 3), multiply(4, 5));"
            const expectedCppCode =
                "auto result = calculate(add(static_cast<int>(2), static_cast<int>(3)), multiply(static_cast<int>(4), static_cast<int>(5)));"

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            )
        })
    })
})

describe("generating operators and arithmetic expressions", function () {
    it("should convert addition operator", function () {
        const jsCode = "const sum = a + b;"
        const expectedCppCode = "auto sum = (a + b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert subtraction operator", function () {
        const jsCode = "const difference = x - y;"
        const expectedCppCode = "auto difference = (x - y);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert multiplication operator", function () {
        const jsCode = "const product = x * y;"
        const expectedCppCode = "auto product = (x * y);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert division operator", function () {
        const jsCode = "const quotient = a / b;"
        const expectedCppCode = "auto quotient = (a / b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert modulo operator", function () {
        const jsCode = "const remainder = x % y;"
        const expectedCppCode = "auto remainder = (x % y);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should handle complex arithmetic expressions", function () {
        const jsCode = "const result = (a + b) * (c - d) / e;"
        const expectedCppCode = "auto result = (((a + b) * (c - d)) / e);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating assignment operators", function () {
    it("should convert assignment operator", function () {
        const jsCode = "x = 42;"
        const expectedCppCode = "x = static_cast<int>(42);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert addition assignment operator", function () {
        const jsCode = "x += 10;"
        const expectedCppCode = "x = x + static_cast<int>(10) ;"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert subtraction assignment operator", function () {
        const jsCode = "x -= 5;"
        const expectedCppCode = "x -= static_cast<int>(5);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert multiplication assignment operator", function () {
        const jsCode = "x *= 2;"
        const expectedCppCode = "x *= static_cast<int>(2);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert division assignment operator", function () {
        const jsCode = "x /= 3;"
        const expectedCppCode = "x /= static_cast<int>(3);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert modulo assignment operator", function () {
        const jsCode = "x %= 4;"
        const expectedCppCode = "x %= static_cast<int>(4);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating comparison and logical operators", function () {
    it("should convert equality comparison operator", function () {
        const jsCode = "x === 42;"
        const expectedCppCode = "(x == static_cast<int>(42));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert inequality comparison operator", function () {
        const jsCode = "x !== 10;"
        const expectedCppCode = "(x != static_cast<int>(10));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert greater than comparison operator", function () {
        const jsCode = "x > 5;"
        const expectedCppCode = "(x > static_cast<int>(5));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert less than comparison operator", function () {
        const jsCode = "x < 8;"
        const expectedCppCode = "(x < static_cast<int>(8));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert greater than or equal to comparison operator", function () {
        const jsCode = "x >= 15;"
        const expectedCppCode = "(x >= static_cast<int>(15));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert less than or equal to comparison operator", function () {
        const jsCode = "x <= 20;"
        const expectedCppCode = "(x <= static_cast<int>(20));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert logical AND operator", function () {
        const jsCode = "x && y;"
        const expectedCppCode = "(x && y);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert logical OR operator", function () {
        const jsCode = "x || y;"
        const expectedCppCode = "(x || y);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert logical NOT operator", function () {
        const jsCode = "!x;"
        const expectedCppCode = "JS_CAST_ExclamationBoolean(x);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating conditional statements", function () {
    it("should convert if statement without else", function () {
        const jsCode = "if (x > 10) { true; }"
        const expectedCppCode = "if ((x > static_cast<int>(10))) { true; }"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert if statement with else", function () {
        const jsCode = "if (x > 10) { true; } else { false; }"
        const expectedCppCode =
            "if ((x > static_cast<int>(10))) { true; } else { false; }"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert else if statement", function () {
        const jsCode = `
      if (x > 10) {
        true;
      } else if (x > 5) {
        true;
      }
    `
        const expectedCppCode = `
      if ((x > static_cast<int>(10))) {
        true;
      } else if ((x > static_cast<int>(5))) {
        true;
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert if-else statement with nested statements", function () {
        const jsCode = `
      if (x > 10) {
        if (y > 5) {
          true;
        } else {
          true;
        }
      } else {
        true;
      }
    `
        const expectedCppCode = `
      if ((x > static_cast<int>(10))) {
        if ((y > static_cast<int>(5))) {
          true;
        } else {
         true;
        }
      } else {
        true;
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating switch statements", function () {
    it("should convert switch statement with cases", function () {
        const jsCode = `
      switch (x) {
        case 1:
          "one";
          break;
        case 2:
          "two";
          break;
        default:
          "other";
      }
    `
        const expectedCppCode = `
      switch (x) {
        case static_cast<int>(1):
          std::string("one");
          break;
        case static_cast<int>(2):
          std::string("two");
          break;
        default:
          std::string("other");
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert switch statement with fallthrough", function () {
        const jsCode = `
      switch (x) {
        case 1:
          "one";
        case 2:
          "two";
          break;
        default:
          "other";
      }
    `
        const expectedCppCode = `
      switch (x) {
        case static_cast<int>(1):
          std::string("one");
        case static_cast<int>(2):
          std::string("two");
          break;
        default:
          std::string("other");
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating loops", function () {
    it("should convert for loop to C++ for loop", function () {
        const jsCode = `
      for (let i = 0; i < 10; i++) {
        "loop body";
      }
    `
        const expectedCppCode = `
      for (auto i = static_cast<int>(0); (i < static_cast<int>(10)); i++) {
        std::string("loop body");
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert for...in loop to C++ range-based for loop", function () {
        const jsCode = `
      for (let key in object) {
        "loop body";
      }
    `
        const expectedCppCode = `
      for (const auto& entry : object) {
        auto key = entry.first;
        std::string("loop body");
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert for...of loop to C++ range-based for loop", function () {
        const jsCode = `
      for (let item of array) {
        "loop body";
      }
    `
        const expectedCppCode = `
      for (const auto& item : array) {
        std::string("loop body");
      }
    `

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating While loops", function () {
    it("should convert while loop to C++ while loop", function () {
        const jsCode = "while (x > 0) { x--; }"
        const expectedCppCode = "while ((x > static_cast<int>(0))) { x--; }"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert do...while loop to C++ do...while loop", function () {
        const jsCode = "do { x--; } while (x > 0);"
        const expectedCppCode = "do { x--; } while ((x > static_cast<int>(0)));"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

describe("generating bitwise operations", function () {
    it("should convert bitwise AND operation to C++", function () {
        const jsCode = "const result = a & b;"
        const expectedCppCode = "auto result = (a & b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert bitwise OR operation to C++", function () {
        const jsCode = "const result = a | b;"
        const expectedCppCode = "auto result = (a | b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert bitwise XOR operation to C++", function () {
        const jsCode = "const result = a ^ b;"
        const expectedCppCode = "auto result = (a ^ b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert bitwise NOT operation to C++", function () {
        const jsCode = "const result = ~a;"
        const expectedCppCode = "auto result = ~a;"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert left shift operation to C++", function () {
        const jsCode = "const result = a << b;"
        const expectedCppCode = "auto result = (a << b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })

    it("should convert right shift operation to C++", function () {
        const jsCode = "const result = a >> b;"
        const expectedCppCode = "auto result = (a >> b);"

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        )
    })
})

function translateToCppWithDefaults(jsCode) {
    return generateCpp(acorn.parse(jsCode), { numberDataType: "int" })
}
