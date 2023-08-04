// Variable Declarations and Initialization
let a = 5;
const b = 10;

// Variable Reassignment
a = 15;

// Variable Scopes
function exampleFunction() {
  var x = 20;
  let y = 30;
  if (true) {
    var x = 40; // This will modify the outer 'x' as well
    let y = 50; // This 'y' is scoped to the block
    console.log(x); // Output: 40
    console.log(y); // Output: 50
  }
  console.log(x); // Output: 40
  console.log(y); // Output: 30 (the outer 'y')
}
exampleFunction();

// Hoisting
console.log(num); // Output: undefined (variable exists but not assigned a value yet)
var num = 100;

// Closure
function outerFunction() {
  const outerVar = 'I am from outerFunction';
  return function innerFunction() {
    console.log(outerVar);
  };
}
const innerFunc = outerFunction();
innerFunc(); // Output: I am from outerFunction

// IIFE (Immediately Invoked Function Expression)
(function () {
  console.log('I am an IIFE!');
})();

// Destructuring Assignment
const obj = { x: 1, y: 2 };
const { x, y } = obj;
console.log(x, y); // Output: 1 2

// Default Parameter Values
function greet(name = 'John') {
  console.log(`Hello, ${name}!`);
}
greet(); // Output: Hello, John!
greet('Alice'); // Output: Hello, Alice!

// Rest Parameter
function sum(...numbers) {
  let total = 0;
  for (const num of numbers) {
    total += num;
  }
  return total;
}
const sumResult = sum(1, 2, 3, 4, 5);
console.log(sumResult); // Output: 15

// Spread Operator
const arr1 = [1, 2, 3];
const arr2 = [4, 5, 6];
const combinedArr = [...arr1, ...arr2];
console.log(combinedArr); // Output: [1, 2, 3, 4, 5, 6]

// Template Literal
const name = 'Alice';
const age = 30;
const message = `My name is ${name} and I am ${age} years old.`;
console.log(message); // Output: My name is Alice and I am 30 years old.

// Rest Properties
const { x: var1, y: var2, ...rest } = { x: 1, y: 2, z: 3, a: 4 };
console.log(var1, var2); // Output: 1 2
console.log(rest); // Output: { z: 3, a: 4 }

// Object Shorthand
const xValue = 10;
const yValue = 20;
const obj2 = { xValue, yValue };
console.log(obj2); // Output: { xValue: 10, yValue: 20 }

// Object Destructuring
const person = { firstName: 'John', lastName: 'Doe', age: 25 };
const { firstName, lastName, age: personAge } = person;
console.log(firstName, lastName, personAge); // Output: John Doe 25

// Object Spread
const person2 = { ...person, city: 'New York' };
console.log(person2); // Output: { firstName: 'John', lastName: 'Doe', age: 25, city: 'New York' }
