console.time("Heyo")
let i = 0
while (true) {
  i += .0004
  if (i >= 10000) {
    break
  }
}
console.timeEnd("Heyo")
