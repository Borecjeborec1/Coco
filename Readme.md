# Coco: JavaScript to C++ Compiler v0.0.0

![Coco Logo](logo.png)

Coco is a personal project created by a regular high school student that allows you to compile JavaScript code by translating it into C++. This approach opens up exciting possibilities for integrating C++ with Node.js applications. Whether you're looking to improve performance, take advantage of C++ libraries, or explore new possibilities, Coco is here to help.

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Examples](#examples)
5. [Contributing](#contributing)
6. [License](#license)

## Features

JavaScript is a popular programming language, primarily known for its versatility and its role in web development. However, certain applications, especially those requiring high performance or low-level system interactions, may benefit from the capabilities of C++, a powerful systems programming language. Coco bridges the gap between these two worlds, offering the following advantages:

-   **JavaScript to C++ Compilation**: Translate your JavaScript code into C++ for enhanced performance and integration possibilities.

-   **Node.js Compatible**: Coco is designed to work seamlessly with Node.js applications, allowing you to harness the power of C++ within your JavaScript projects.

-   **Automatic Type Inference**: Coco automatically infers data types where possible, reducing the need for manual type annotations.

-   **Standard Library Integration**: Easily integrate C++ standard library functions and modules into your JavaScript code.

-   **Customization**: Configure Coco's behavior using options and settings to tailor the compilation process to your specific needs.

-   **Extensibility**: Coco is built with extensibility in mind, making it easy to add custom translation rules and support for additional JavaScript features.

-   **C++11 Compatible**: The C++ code generated by Coco is written in C++11, providing you with the benefits of modern C++ features and compatibility.

## Installation

## Usage

Using Coco is straightforward. You can compile your JavaScript code to C++ by running the following command:

```shell
coco <input_file.js>
```

-   _<input_file.js>:_ Replace this with the path to your JavaScript source file that you want to compile.

#### Configuration Options:

Coco supports various configuration options that allow you to customize the compilation process

-   `-v`, `--version`: Display the Coco version.

-   `--time-output`, `--time-outputs`: Measure and display the time taken for the compilation process.

-   `-o <output_file>`, `--output <output_file>`: Specify the name of the output file where the generated C++ code will be saved.

-   `--cpp <cpp_file>`: Specify the name of the C++ source file to be generated.

-   `--useFloat`: Specify the use of a `double` data type for all the numbers in the generated C++ code. By default, Coco uses `int` as the data type.

-   `--useBigInt`: Specify the use of a `long long` data type for all the numbers in the generated C++ code if you dont want to anotate everything.

#### Linking C++ Code to JavaScript

Coco empowers you to seamlessly integrate C++ code into your JavaScript applications, allowing you to leverage the performance benefits and vast libraries of C++. Below is a more complex example demonstrating how to link C++ code to a JavaScript file:

**JavaScript File (app.js):**

```javascript
const { calculateFibonacci } = require("./fibonacci.cpp");

// Calculate and print the Fibonacci sequence
const n = 10;
const fibonacciSequence = calculateFibonacci(n);
console.log(
    `Fibonacci sequence of ${n} numbers: ${fibonacciSequence.join(", ")}`
);
```

**C++ File (fibonacci.cpp):**

```javascript
#include <vector>

// Function to calculate the Fibonacci sequence up to n numbers
std::vector<int> calculateFibonacci(int n) {
    std::vector<int> sequence;
    if (n >= 1) sequence.push_back(0);
    if (n >= 2) sequence.push_back(1);

    for (int i = 2; i < n; ++i) {
        int nextNumber = sequence[i - 1] + sequence[i - 2];
        sequence.push_back(nextNumber);
    }

    return sequence;
}
```

In this example, we have an app.js JavaScript file that requires and uses a C++ function calculateFibonacci defined in the fibonacci.cpp file. The C++ function calculates the Fibonacci sequence up to a specified number of terms and returns the result as an array. You can seamlessly run this JavaScript code, and Coco will handle the integration of the C++ code into your Node.js application.

This powerful feature opens up endless possibilities for combining the strengths of both languages to create high-performance and feature-rich applications. Whether you need to optimize computationally-intensive tasks, utilize C++ libraries, or simply explore new capabilities, Coco has you covered.

## Example:

Examples are not written yet. But you can look inside the translation tests in [tests/JS/js.test.js](./tests/JS/js.test.js).

## Contributing

Coco is an open-source project, and contributions are welcome! If you have ideas, bug fixes, or feature improvements, please open an [issue](https://github.com/Borecjeborec1/Coco/issues) or submit a [pull request](https://github.com/Borecjeborec1/Coco/pulls).

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
