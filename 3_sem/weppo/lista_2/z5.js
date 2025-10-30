const car = { make: "Toyota" };

car.model = "Corolla";

console.log(car);

car.start = function () {
  return `${this.make} ${this.model}`;
};
console.log(car.start());

console.log(car);
Object.defineProperty(car, "year", {
  get() {
    return this._year;
  },
  set(value) {
    this._year = value;
  },
  enumerable: true,
});
car.year = 2022;
console.log(car);
console.log(car.year);
