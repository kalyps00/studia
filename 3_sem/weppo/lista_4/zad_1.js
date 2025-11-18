function getLastProto(o) {
  let p = o;
  do {
    o = p;
    p = Object.getPrototypeOf(o);
  } while (p);
  return o;
}
//kazdy obiekt stworzony przez {} lub  konstruktor Object
let obj1 = {};
let obj2 = new Object();
let arr = [1, 2, 3];
let func = function () {};
let date = new Date();

let proto1 = getLastProto(obj1);
let proto2 = getLastProto(obj2);
let proto3 = getLastProto(arr);
let proto4 = getLastProto(date);

console.log("obj1 === obj2:", proto1 === proto2);
console.log("obj1 === arr:", proto1 === proto3);
console.log("obj1 === date:", proto1 === proto4);
console.log("Wszystkie === Object.prototype:", proto1 === Object.prototype);
