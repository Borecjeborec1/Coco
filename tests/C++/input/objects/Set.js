const set = new Set();

console.log("Set.prototype.size (Initial Size):", set.size);

set.add("value1");
set.add("value2");
set.add("value3");

console.log("Set.prototype.size (After Adding Values):", set.size);

console.log("Set.prototype.has('value2'):", set.has("value2"));
console.log("Set.prototype.has('value4'):", set.has("value4"));

set.delete("value3");
console.log("Set.prototype.size (After Deleting Value):", set.size);

set.clear();
console.log("Set.prototype.size (After Clearing):", set.size);

set.add("Alice");
set.add("Bob");
set.add("Charlie");

console.log("Set Values:");
for (const value of set.values()) {
    console.log(value);
}

// const setToArray = [...set];
// console.log("Set converted to Array:", setToArray);

const obj1 = { id: 1 };
const obj2 = { id: 2 };

set.add(obj1);
set.add(obj2);

console.log("Set.prototype.has(obj1):", set.has(obj1));
console.log("Set.prototype.has(obj2):", set.has(obj2));

set.add(42);
set.add(true);
set.add("stringValue");

console.log("Set.prototype.has(42):", set.has(42));
console.log("Set.prototype.has(true):", set.has(true));
console.log("Set.prototype.has('stringValue'):", set.has("stringValue"));
