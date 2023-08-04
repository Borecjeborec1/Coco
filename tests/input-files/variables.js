let x = 10;
const PI = -3.14;
var y = 'Hello';
console.log(x);
console.log(y);

function exampleFunction() {
  var x = 1000;
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