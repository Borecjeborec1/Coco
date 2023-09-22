const currentDate = new Date()
console.log(currentDate.getDate())
// // console.log("Date.prototype.constructor:", currentDate.constructor)
// console.log("Date.prototype.toString:", currentDate.toString())
// console.log("Date.prototype.toDateString:", currentDate.toDateString())
// console.log("Date.prototype.toTimeString:", currentDate.toTimeString())
// console.log("Date.prototype.toISOString:", currentDate.toISOString())
// console.log("Date.prototype.toJSON:", currentDate.toJSON())
// console.log("Date.prototype.valueOf:", currentDate.valueOf())
console.log("Date.prototype.getDate:", currentDate.getDate())
console.log("Date.prototype.getDay:", currentDate.getDay())
console.log("Date.prototype.getFullYear:", currentDate.getFullYear())
console.log("Date.prototype.getHours:", currentDate.getHours())
// console.log("Date.prototype.getMilliseconds:", currentDate.getMilliseconds())
console.log("Date.prototype.getMinutes:", currentDate.getMinutes())
console.log("Date.prototype.getMonth:", currentDate.getMonth())
console.log("Date.prototype.getSeconds:", currentDate.getSeconds())
// console.log("Date.prototype.getTime:", currentDate.getTime())
// console.log(
//     "Date.prototype.getTimezoneOffset:",
//     currentDate.getTimezoneOffset()
// )

// // Date Object Methods
console.log("Date.now:", Date.now().toString().substring(0, 5))
console.log("Date.UTC:", Date.UTC(2023, 0, 15))
console.log("Date.parse:", Date.parse("2023-01-15T12:00:00Z"))
// // console.log("Date.parse (Invalid Date):", Date.parse("Invalid Date"))

// Set Methods (Modify the Date object)
currentDate.setFullYear(2024)
console.log("Date.prototype.setFullYear:")
console.log("Date.prototype.getFullYear:", currentDate.getFullYear())
currentDate.setMonth(4)
console.log("Date.prototype.setMonth:")
console.log("Date.prototype.getMonth:", currentDate.getMonth())
currentDate.setDate(29)
console.log("Date.prototype.setDate:")
console.log("Date.prototype.getDate:", currentDate.getDate())
currentDate.setHours(10)
console.log("Date.prototype.setHours:")
console.log("Date.prototype.getHours:", currentDate.getHours())
currentDate.setMinutes(30)
console.log("Date.prototype.setMinutes:")
console.log("Date.prototype.getMinutes:", currentDate.getMinutes())
currentDate.setSeconds(45)
console.log("Date.prototype.setSeconds:")
console.log("Date.prototype.getSeconds:", currentDate.getSeconds())
currentDate.setMilliseconds(500)
console.log("Date.prototype.setMilliseconds:")
console.log("Date.prototype.getMilliseconds:", currentDate.getMilliseconds())

console.log("Date.prototype.getDay:", currentDate.getDay())

// Other Methods
// console.log("Date.prototype.toUTCString:", currentDate.toUTCString()) // moved by 2 hours
// console.log("Date.prototype.toLocaleString:", currentDate.toLocaleString()) // Working with extra 0 on start
// console.log(
//     "Date.prototype.toLocaleDateString:",
//     currentDate.toLocaleDateString()
// ) // Working with extra 0 on start day
// console.log(
//     "Date.prototype.toLocaleTimeString:",
//     currentDate.toLocaleTimeString()
// )

// // Comparison Methods
const futureDate = new Date(2025, 0, 1)
console.log(
    "Date.prototype.getTime() vs. futureDate.getTime():",
    currentDate.getTime() < futureDate.getTime()
)

// // Example: Formatting a Date
// const options = {
//     weekday: "long",
//     year: "numeric",
//     month: "long",
//     day: "numeric",
// }
// console.log(
//     "Formatted Date:",
//     currentDate.toLocaleDateString(undefined, options)
// )
