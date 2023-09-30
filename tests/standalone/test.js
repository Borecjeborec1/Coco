// import test from "./importFrom.js";
// import { sum, subst } from "./importFrom.js";
const test = require("./importFrom.js");
const { summ = 5, subst } = require("./importFrom.js");

console.log(summ);
console.log(test.sum(1, 2));
