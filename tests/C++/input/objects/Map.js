const map = new Map();

console.log("Map.prototype.size (Initial Size):", map.size);

map.set("key1", "value1");
map.set("key2", "value2");
map.set("key3", "value3");

console.log("Map.prototype.size (After Adding Entries):", map.size);

console.log("Map.prototype.get('key1'):", map.get("key1"));
// console.log("Map.prototype.get('key4') (Non-existent key):", map.get("key4"));

console.log("Map.prototype.has('key2'):", map.has("key2"));
console.log("Map.prototype.has('key4'):", map.has("key4"));

map.delete("key3");
console.log("Map.prototype.size (After Deleting Entry):", map.size);

map.clear();
console.log("Map.prototype.size (After Clearing):", map.size);

map.set("Alice", 25);
map.set("Bob", 30);
map.set("Charlie", 22);

console.log("Map Entries:");
for (const [key, value] of map.entries()) {
    console.log(value);
}

console.log("Map Keys:");
for (const key of map.keys()) {
    console.log(key);
}

console.log("Map Values:");
for (const value of map.values()) {
    console.log(value);
}

// const mapToArray = [...map];
// console.log("Map converted to Array:", mapToArray);

// const mapToObject = Object.fromEntries(map);
// console.log("Map converted to Object:", mapToObject);
