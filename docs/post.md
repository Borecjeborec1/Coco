# Introducing Coco v0.0.1: Where JavaScript Meets Lightning-Speed C++

_TL;DR: Random developer created js "translator" into the c++. Now he craves for some github stars. Repo link: GITHUB_REPO_LINK_

About half a year ago I´ve started this project, to be able to use js as a fast language for some CP (Competetive programming) projects. As time went on... bun vs node wars ... decided to publish it. So here it is.

Coco is a rly simply written translator that translates js code to c++. Nearly every living object (except some humans) can understand its source code.

-   Briefly how it translates
-   Advantages
    -   Compiled
    -   Speed
    -   Linking c++ code (shwocase some GUI)
    -   Some node modules built in

Oh, you thought Node.js was fast? Well, think again! We present to you the future of JavaScript development, and it's so fast that even the speed of light is struggling to keep up.

### What is Coco?

Coco is not just another JavaScript runtime; it's a quantum leap in JavaScript evolution. We take your humble JavaScript code, turn it into an Abstract Syntax Tree (AST), and then magically transform it into C++. The result?**Blazingly-fast** performance and **unparalleled** execution speed.

### Why Use Coco?

-   **Speed:** Your code will run so fast that it's basically time travel.
-   **Compatibility**: We've already hacked into the minds of popular Node.js modules to make them work seamlessly with Coco.
-   **Compile It All:** Transform your JavaScript into native, platform-specific binaries. Who needs interpreters when you can have that?
-   **C++11 Compatibility:** Coco's generated C++ code is designed with compatibility in mind. It's based on the robust C++11 standard, ensuring it plays nice with older C++ versions. So no any or variants and all is declared already in compile time.

### How to Get Started

Install it: `npm install -g coco`
Run your code: `coco your-file.js`

##### Contributions

Our Contributors _(just me)_ Are Basically Superheroes.
But I am inviting you to join me and contribute/implemenent anything you want.

### What's Next?

Prepare yourself for a JavaScript renaissance. It's time to replace your coffee breaks with blink-and-you'll-miss-it execution speed. Give Coco a try, and let us know what you think. I am pretty sure you'll love it because, well, who wouldn't?

Get ready for the JavaScript revolution. Don't just like or star us, prepare to be utterly obsessed.

### Linking C++ Code to JavaScript

Coco isn't just about speeding up your JavaScript, it's about opening the door to a world of possibilities by integrating C++ seamlessly into your applications. This means you can harness the incredible performance and extensive libraries of C++ while still enjoying the flexibility and readability of JavaScript.

Showcasing the Magic
Check out this impressive example of how you can link C++ code to your JavaScript applications:

JavaScript File (app.js):

```javascript
const { calculateFibonacci } = require("./fibonacci.cpp");

// Calculate and print the Fibonacci sequence
const n = 10;
const fibonacciSequence = calculateFibonacci(n);
console.log(
    `Fibonacci sequence of ${n} numbers: ${fibonacciSequence.join(", ")}`
);
```

C++ File (fibonacci.cpp):

```cpp
#include <vector>

std::vector<int> calculateFibonacci(int n) {
    std::vector<int> sequence;
    if (n >= 1) sequence push_back(0);
    if (n >= 2) sequence push_back(1);

    for (int i = 2; i < n; ++i) {
        int nextNumber = sequence[i - 1] + sequence[i - 2];
        sequence.push_back(nextNumber);
    }

    return sequence;
}
```

In this example, we have an app.js JavaScript file that seamlessly requires and utilizes a C++ function called `calculateFibonacci`, which is defined in the `fibonacci.cpp `file. This C++ function calculates the Fibonacci sequence up to a specified number of terms and returns the result as an array. Running this JavaScript code is a breeze, and Coco handles all the complexities of integrating the C++ code into your Node.js application.

With Coco, you unlock the potential to blend the best of both worlds. Optimize computationally-intensive tasks, tap into C++ libraries, or explore new frontiers in your applications. The power is in your hands, and Coco is here to make it easy.

### Caveats? Coco Got a Few!

Okay, I got to be honest with you – even though we believe Coco is the bee's knees, it's not all rainbows and butterflies. There are a couple of things you should know:

##### Slightly Longer Compile Time

You see, Coco code sorcery is so powerful that it takes a little extra time to weave its magic. Compiling can take a tad longer than you might be used to because C++ is linking all the necessary libraries to create the ultimate performance masterpiece.

But let's be real, in this age of instant gratification, who even cares about compile time anymore? It's like waiting for your coffee to brew – you know it'll be worth the wait.

##### Not a Syntax Omniscient Wizard

I admit it – it is not omniscient (yet). Coco doesn't support every single JavaScript syntax out there. I am like the discerning gourmet chef who carefully selects the finest ingredients for the best dishes. So, some obscure, dusty corners of JavaScript might not be in Coco repertoire. But honestly, who needs those overly complicated, fringe features anyway?
But I still implemented some :D.

In summary, it is not perfect, but I am working tirelessly to improve and expand Coco capabilities. I am confident that, despite these tiny quirks, you'll fall head over heels for Coco's performance and potential.

So, what are you waiting for? Embrace the future of JavaScript, quirks and all!
