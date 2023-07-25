class Rectangle {
  constructor(width, height) {
    this.width = width;
    this.height = height;
  }

  get area() {
    return this.width * this.height;
  }

  set area(value) {
    this.width = Math.sqrt(value);
    this.height = Math.sqrt(value);
  }

  static createSquare(size) {
    return new Rectangle(size, size);
  }
}

const rect = new Rectangle(5, 10);
console.log(rect.area);

rect.area = 100;
console.log(rect.width, rect.height);

const square = Rectangle.createSquare(20);
console.log(square.width, square.height);