console.time("Test")
console.log("testing")
let x = { x: 12 }
for (let i = 0; i < 1000000; i++) {
  let abc = i * i + 123
}
console.timeEnd("Test")
