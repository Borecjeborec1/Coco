const person = {
  name: 'John',
  age: 30,
  address: {
    city: 'New York',
    country: 'USA'
  }
};

console.log(person.name);
console.log(person.address.city);

person.job = 'Engineer';
console.log(person);

delete person.age;
console.log(person);
