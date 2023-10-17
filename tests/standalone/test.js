// Function to generate a random integer between min and max (inclusive)
function getRandomInt(_min, _max) {
    return Math.floor(Math.random() * (_max - _min + 1)) + _min;
}
console.log(getRandomInt(1, 300));
