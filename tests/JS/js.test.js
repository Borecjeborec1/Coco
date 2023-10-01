const { expect, use } = require("chai");
const chaiString = require("chai-string");
const { generateCpp, generateRandomString } = require("../../src/main"); // Adjust the path accordingly
const acorn = require("acorn");
const { tsPlugin } = require("acorn-typescript");

use(chaiString);

describe("Generating variable types", function () {
    it("should convert let variables to C++ auto", function () {
        const jsCode = "let x = 42";
        const expectedCppCode = "auto x = static_cast<int>(42);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert var variables to C++ auto", function () {
        const jsCode = "var x = 42;";
        const expectedCppCode = "auto x = static_cast<int>(42);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert const variables to C++ auto", function () {
        const jsCode = "const x = 42;";
        const expectedCppCode = "auto x = static_cast<int>(42);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating data types", function () {
    it("should convert positive number to C++ int", function () {
        const variableValue = 42;
        const jsCode = `let x = ${variableValue};`;
        const expectedCppCode = `auto x = static_cast<int>(${variableValue});`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert negative number to C++ int", function () {
        const variableValue = -42;
        const jsCode = `let x = ${variableValue};`;
        const expectedCppCode = `auto x = static_cast<int>(0) - static_cast<int>(42);`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert string to C++ std::string", function () {
        const variableValue = `"test-string"`;
        const jsCode = `let x = ${variableValue};`;
        const expectedCppCode = `auto x = std::string(${variableValue});`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert boolean to C++ bool", function () {
        const variableValue = `true`;
        const jsCode = `let x = ${variableValue};`;
        const expectedCppCode = `auto x = ${variableValue};`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert undefined to C++ empty json", function () {
        const jsCode = `let x = undefined;`;
        const expectedCppCode = `auto x = nlohmann::json();`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert null to C++ empty json", function () {
        const jsCode = `let x = null;`;
        const expectedCppCode = `auto x = nlohmann::json();`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert NaN to C++ empty json", function () {
        const jsCode = `let x = NaN;`;
        const expectedCppCode = `auto x = nlohmann::json();`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating objects and arrays", function () {
    it("should convert array C++ nlohmann::json", function () {
        const variableValue = `[12]`;
        const jsCode = `let x = ${variableValue};`;

        const expectedCppCode = `auto x = nlohmann::json{static_cast<int>(12)};`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert array with different data types to C++ nlohmann::json", function () {
        const variableValue = `[12, "test", true]`;
        const jsCode = `let x = ${variableValue};`;
        const expectedCppCode = `auto x = nlohmann::json{static_cast<int>(12), std::string("test"), true};`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert object literal to C++ nlohmann::json", function () {
        const jsCode = 'let obj = { x: 12, y: "test", z: true };';
        const expectedCppCode =
            'auto obj = nlohmann::json{{"x", static_cast<int>(12)}, {"y", std::string("test")}, {"z", true}};';

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert nested object and array literal to C++ nlohmann::json", function () {
        const jsCode = "let data = { x: { y: [1, 2, 3] } };";
        const expectedCppCode =
            'auto data = nlohmann::json{{"x", nlohmann::json{{"y", nlohmann::json{static_cast<int>(1), static_cast<int>(2), static_cast<int>(3)}}}}};';

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating function", function () {
    describe("and declaring them", function () {
        it("should convert function declaration to C++ lambda", function () {
            const jsCode = "function add(a, b) { return a + b; }";
            const expectedCppCode =
                "auto add = [](auto a, auto b) { return (a + b); };";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });

        it("should convert arrow function declaration without block to C++ lambda", function () {
            const jsCode = "const square = x => x * x;";
            const expectedCppCode =
                "auto square = [](auto x) { return (x * x); };";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });

        it("should convert arrow function declaration with block to C++ lambda", function () {
            const jsCode = "const add = (a, b) => { return a + b; };";
            const expectedCppCode =
                "auto add = [](auto a, auto b) { return (a + b); };";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });
    });

    describe("and calling them", function () {
        it("should convert function call to C++ lambda invocation", function () {
            const jsCode = "add(2, 3);";
            const expectedCppCode = `add(static_cast<int>(2), static_cast<int>(3));`;

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });

        it("should convert arrow function call to C++ lambda invocation", function () {
            const jsCode = "const result = multiply(5, 3);";
            const expectedCppCode =
                "auto result = multiply(static_cast<int>(5), static_cast<int>(3));";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });

        it("should handle nested function calls with different argument types", function () {
            const jsCode =
                "const result = calculate(add(2, 3), multiply(4, 5));";
            const expectedCppCode =
                "auto result = calculate(add(static_cast<int>(2), static_cast<int>(3)), multiply(static_cast<int>(4), static_cast<int>(5)));";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });
    });
});

describe("Generating operators and arithmetic expressions", function () {
    it("should convert addition operator", function () {
        const jsCode = "const sum = a + b;";
        const expectedCppCode = "auto sum = (a + b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert subtraction operator", function () {
        const jsCode = "const difference = x - y;";
        const expectedCppCode = "auto difference = (x - y);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert multiplication operator", function () {
        const jsCode = "const product = x * y;";
        const expectedCppCode = "auto product = (x * y);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert division operator", function () {
        const jsCode = "const quotient = a / b;";
        const expectedCppCode = "auto quotient = (a / b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert modulo operator", function () {
        const jsCode = "const remainder = x % y;";
        const expectedCppCode = "auto remainder = (x % y);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should handle complex arithmetic expressions", function () {
        const jsCode = "const result = (a + b) * (c - d) / e;";
        const expectedCppCode = "auto result = (((a + b) * (c - d)) / e);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating assignment operators", function () {
    it("should convert assignment operator", function () {
        const jsCode = "x = 42;";
        const expectedCppCode = "x = static_cast<int>(42);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert addition assignment operator", function () {
        const jsCode = "x += 10;";
        const expectedCppCode = "x = x + static_cast<int>(10) ;";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert subtraction assignment operator", function () {
        const jsCode = "x -= 5;";
        const expectedCppCode = "x -= static_cast<int>(5);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert multiplication assignment operator", function () {
        const jsCode = "x *= 2;";
        const expectedCppCode = "x *= static_cast<int>(2);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert division assignment operator", function () {
        const jsCode = "x /= 3;";
        const expectedCppCode = "x /= static_cast<int>(3);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert modulo assignment operator", function () {
        const jsCode = "x %= 4;";
        const expectedCppCode = "x %= static_cast<int>(4);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating comparison and logical operators", function () {
    it("should convert equality comparison operator", function () {
        const jsCode = "x === 42;";
        const expectedCppCode = "(x == static_cast<int>(42));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert inequality comparison operator", function () {
        const jsCode = "x !== 10;";
        const expectedCppCode = "(x != static_cast<int>(10));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert greater than comparison operator", function () {
        const jsCode = "x > 5;";
        const expectedCppCode = "(x > static_cast<int>(5));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert less than comparison operator", function () {
        const jsCode = "x < 8;";
        const expectedCppCode = "(x < static_cast<int>(8));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert greater than or equal to comparison operator", function () {
        const jsCode = "x >= 15;";
        const expectedCppCode = "(x >= static_cast<int>(15));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert less than or equal to comparison operator", function () {
        const jsCode = "x <= 20;";
        const expectedCppCode = "(x <= static_cast<int>(20));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert logical AND operator", function () {
        const jsCode = "x && y;";
        const expectedCppCode = "(x && y);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert logical OR operator", function () {
        const jsCode = "x || y;";
        const expectedCppCode = "(x || y);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert logical NOT operator", function () {
        const jsCode = "!x;";
        const expectedCppCode = "JS_CAST_ExclamationBoolean(x);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating conditional statements", function () {
    it("should convert if statement without else", function () {
        const jsCode = "if (x > 10) { true; }";
        const expectedCppCode = "if ((x > static_cast<int>(10))) { true; }";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert if statement with else", function () {
        const jsCode = "if (x > 10) { true; } else { false; }";
        const expectedCppCode =
            "if ((x > static_cast<int>(10))) { true; } else { false; }";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert else if statement", function () {
        const jsCode = `
      if (x > 10) {
        true;
      } else if (x > 5) {
        true;
      }
    `;
        const expectedCppCode = `
      if ((x > static_cast<int>(10))) {
        true;
      } else if ((x > static_cast<int>(5))) {
        true;
      }
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

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
    `;
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
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating switch statements", function () {
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
    `;
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
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

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
    `;
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
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating loops", function () {
    it("should convert for loop to C++ for loop", function () {
        const jsCode = `
      for (let i = 0; i < 10; i++) {
        "loop body";
      }
    `;
        const expectedCppCode = `
      for (auto i = static_cast<int>(0); (i < static_cast<int>(10)); i++) {
        std::string("loop body");
      }
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert for loop with big numbers to C++ for loop with long long", function () {
        const jsCode = `
      for (let i = 0; i < 1000000000; i++) {
        "loop body";
      }
    `;
        const expectedCppCode = `
      for (auto i = static_cast<long long int>(0); (i < static_cast<long long int>(1000000000)); i++) {
        std::string("loop body");
      }
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert for...in loop to C++ range-based for loop", function () {
        const jsCode = `
      for (let key in object) {
        "loop body";
      }
    `;
        const expectedCppCode = `
      for (const auto& entry : object) {
        auto key = entry.first;
        std::string("loop body");
      }
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert for...of loop to C++ range-based for loop", function () {
        const jsCode = `
      for (let item of array) {
        "loop body";
      }
    `;
        const expectedCppCode = `
      for (const auto& item : array) {
        std::string("loop body");
      }
    `;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating While loops", function () {
    it("should convert while loop to C++ while loop", function () {
        const jsCode = "while (x > 0) { x--; }";
        const expectedCppCode = "while ((x > static_cast<int>(0))) { x--; }";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert do...while loop to C++ do...while loop", function () {
        const jsCode = "do { x--; } while (x > 0);";
        const expectedCppCode =
            "do { x--; } while ((x > static_cast<int>(0)));";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating bitwise operations", function () {
    it("should convert bitwise AND operation to C++", function () {
        const jsCode = "const result = a & b;";
        const expectedCppCode = "auto result = (a & b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert bitwise OR operation to C++", function () {
        const jsCode = "const result = a | b;";
        const expectedCppCode = "auto result = (a | b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert bitwise XOR operation to C++", function () {
        const jsCode = "const result = a ^ b;";
        const expectedCppCode = "auto result = (a ^ b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert bitwise NOT operation to C++", function () {
        const jsCode = "const result = ~a;";
        const expectedCppCode = "auto result = ~a;";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert left shift operation to C++", function () {
        const jsCode = "const result = a << b;";
        const expectedCppCode = "auto result = (a << b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });

    it("should convert right shift operation to C++", function () {
        const jsCode = "const result = a >> b;";
        const expectedCppCode = "auto result = (a >> b);";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

describe("Generating the ts data types", function () {
    it("should convert int types to C++ int", function () {
        const jsInt = "let result:int = 123;";
        const expectedInt = "int result = 123;";
        const jsLongInt = "let result:lint = 123;";
        const expectedLongInt = "long int result = 123;";
        const jsLongLongInt = "let result:llint = 123;";
        const expectedLongLongInt = "long long int result = 123;";

        expect(translateToCppWithDefaults(jsInt)).to.equalIgnoreSpaces(
            expectedInt
        );
        expect(translateToCppWithDefaults(jsLongInt)).to.equalIgnoreSpaces(
            expectedLongInt
        );
        expect(translateToCppWithDefaults(jsLongLongInt)).to.equalIgnoreSpaces(
            expectedLongLongInt
        );
    });
    it("should convert uint types to C++ unsigned", function () {
        const jsInt = "let result:uint = 123;";
        const expectedInt = "unsigned result = 123;";
        const jsLongInt = "let result:luint = 123;";
        const expectedLongInt = "long unsigned result = 123;";
        const jsLongLongInt = "let result:lluint = 123;";
        const expectedLongLongInt = "long long unsigned result = 123;";

        expect(translateToCppWithDefaults(jsInt)).to.equalIgnoreSpaces(
            expectedInt
        );
        expect(translateToCppWithDefaults(jsLongInt)).to.equalIgnoreSpaces(
            expectedLongInt
        );
        expect(translateToCppWithDefaults(jsLongLongInt)).to.equalIgnoreSpaces(
            expectedLongLongInt
        );
    });
    it("should convert float to C++ double", function () {
        const jsCode = "let result:float = 123;";
        const expectedCppCode = "double result = 123;";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should convert double to C++ double", function () {
        const jsCode = "let result:double = 123;";
        const expectedCppCode = "double result = 123;";

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    describe("and the type is not defined", function () {
        it("should use auto", function () {
            const jsCode = "let result:not_a_valid_type = 123;";
            const expectedCppCode = "auto result =  static_cast<int>(123);";

            expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
                expectedCppCode
            );
        });
    });
});

describe("Generating the destructurable variable", function () {
    it("should destructure simple object", function () {
        const jsCode = "let {x,y} =  idk(1,2);";
        const expectedCppCode = `auto 6leter = idk(static_cast<int>(1), static_cast<int>(2));
        auto x = 6leter["x"];
       auto y = 6leter["y"];`;
        expect(
            translateToCppWithDefaults(jsCode).replace(/ /g, "").length
        ).to.equal(expectedCppCode.replace(/ /g, "").length);
    });

    it("should destructure simple object with defaults", function () {
        const jsCode = "let {x=100,y=100} =  idk(1,2);";
        const expectedCppCode = `auto 6leter = idk(static_cast<int>(1), static_cast<int>(2));
        auto x = 6leter["x"]||static_cast<int>(100);
       auto y = 6leter["y"]||static_cast<int>(100);`;
        expect(
            translateToCppWithDefaults(jsCode).replace(/ /g, "").length
        ).to.equal(expectedCppCode.replace(/ /g, "").length);
    });
    it("should destructure simple object and rename it", function () {
        const jsCode = "let {x:a,y:b} =  idk(1,2);";
        const expectedCppCode = `auto 6leter = idk(static_cast<int>(1), static_cast<int>(2));
        auto a = 6leter["x"];
       auto b = 6leter["y"];`;
        expect(
            translateToCppWithDefaults(jsCode).replace(/ /g, "").length
        ).to.equal(expectedCppCode.replace(/ /g, "").length);
    });
});

describe("Generating the export statements", function () {
    it("should delete line with exports.something", function () {
        const jsCode = "exports.test = some_function";
        const expectedCppCode = ` //  = some_function;`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
    it("should delete line module.exports", function () {
        const jsCode = "module.exports = {some_function}";
        const expectedCppCode = ` //  = nlohmann::json{{"some_function", some_function}};`;

        expect(translateToCppWithDefaults(jsCode)).to.equalIgnoreSpaces(
            expectedCppCode
        );
    });
});

function translateToCppWithDefaults(jsCode) {
    const ast = acorn.Parser.extend(tsPlugin()).parse(jsCode, {
        sourceType: "module",
        ecmaVersion: "latest",
        locations: true,
    });
    return generateCpp(ast, { numberDataType: "int" });
}
