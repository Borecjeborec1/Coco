// Function to generate a random integer between min and max (inclusive)
function getRandomInt(_min, _max) {
    return Math.floor(Math.random() * (_max - _min + 1)) + _min;
}

// Generate a random number between 1 and 100

// // Check if the random number is even or odd
for (let i = 0; i < 10; ++i) {
    const randomNumber = getRandomInt(1, 100);
    console.log(randomNumber);
}
