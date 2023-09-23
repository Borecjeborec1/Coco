const good = Boolean("test"); // use this
const good2 = !!"test"; // or this
const bad = new Boolean("test"); // don't use this!
const bad2 = new Boolean(12321); // don't use this!
const bad3 = new Boolean(true); // don't use this!

console.log(good)
console.log(good2)
console.log(bad)
console.log(bad2)
console.log(bad3)