const good = Boolean("test");
const good2 = !!"test";
const bad = new Boolean("test");
const bad2 = new Boolean(12321);
const bad3 = new Boolean(true);

console.log(good)
console.log(good2)
console.log(bad)
console.log(bad2)
console.log(bad3)