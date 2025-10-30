let x1 = 1;
const x2 = 2;

console.log(x1);

x1 = "Hello";

console.log(x1);

// Lepiej nie tak
var x3 = "Hello";

// Typy danych

// String
let name = "John";

// Number

let age = 25;

// Boolean

let isAdult = true;

// Undefined

let x;

console.log(x);

// Null

let y = null;

// Nie będziemy mówić:

// BigInt

let bigInt = 1234567890123456789012345678901234567890n;

// Symbol
let symbol = Symbol("id");

// ---

// Object

const variable1 = "asdf";

let user = {
  name: "John",
  age: 30,
  1: 3,
  [variable1]: "Hello",
};

console.log(user.name);
console.log(user["name"]);
console.log(user[variable1]);

console.log(user);

const date = new Date("01/01/2020");

console.log(date);

// Type casting

let a = "1";
let b = 2;

let c = b + a;

console.log(c);

console.log("Hello" + " " + "World");

let aNumber1 = Number(a);
let aNumber2 = +a;

console.log(aNumber1);
console.log(aNumber1 + b);
console.log(aNumber2 + b);

let betterC = +a + +b;

console.log(betterC);

let d = a - b;

console.log(d);

console.log(-a + b);

console.log(Number("Hello"));
console.log("ba" + Number("H") + "a");

console.log(parseInt("123.45"));
console.log(parseInt("123asdf"));
console.log(Number("123asdf"));

console.log(String(1234));
console.log("" + 1234);

console.log(Boolean(1));
console.log(Boolean(2));
console.log(Boolean(0));
console.log(Boolean("asd"));
console.log(Boolean("asdasda"));
console.log(Boolean(""));

console.log(Boolean(null));
console.log(Boolean(undefined));

let warunek = 0;

if (warunek) {
  console.log("Hello!");
}

// Truthy and Falsy values
// Falsy values: false, 0, "", null, undefined, NaN
// Truthy values: everything else

let name1 = "";

let number1 = 0;

if (number1) {
  console.log("Validation succeeded");
}

if (name1 !== "" && name1 !== null && name1 !== undefined) {
  console.log("Validation succeeded");
}

// Nie ==  !=
// Tylko === i !==

console.log(1 == "1");
console.log(+1 === +"1");
console.log(1 === "1");
console.log(0 == undefined);
console.log(0 == false);
console.log(undefined == false);

// Funkcje

function sayHello(a) {
  console.log("Hello!", a);
}

sayHello(1);

const sayHello2 = function (a) {
  console.log("Hello!", a);
};

sayHello2(1);

const sayHello3 = (a) => {
  console.log("Hello!", a);
};

sayHello3(1);

function add(a, b = 1) {
  return a + b;
}

const add2 = function (a, b) {
  return a + b;
};

console.log(add(1, 2));
console.log(add(2, 1));
console.log(add(2, 1, 3, 4));
console.log(add(2));
console.log(2 + undefined);

const user2 = {
  name: "John",
  age: 30,
  sayHello: function () {
    console.log("Hello!", this.name);
  },
};

user2.sayHello();

const date2 = new Date("01/01/2020");

console.log(date2.getFullYear());
console.log(date2.getMonth());
console.log(date2.toString());

console.log(Math.max(1, 2, 34, 5, 6, 123, 123345, 2, 3));

// Arrays

const arr = [
  1,
  2,
  3,
  4,
  5,
  "Hello",
  true,
  null,
  undefined,
  [1, 2, 3],
  { name: "John" },
];

console.log(arr[5]);

const numberArray = [5, 4, 3, 2, 1, 10, 11, 21];

function compareNumbers(a, b) {
  return a - b;
}

console.log(compareNumbers(1, 2));
console.log(compareNumbers(2, 1));
console.log(compareNumbers(1, 1));

console.log(numberArray);

console.log(numberArray.sort());
console.log(numberArray.sort(compareNumbers));

console.log(numberArray);

console.log(
  numberArray.map(function (a) {
    return a * 2;
  })
);

console.log(numberArray);

const arrayExample = [1, 2, 3, 4, 5];
const arrayExample2 = arrayExample;

console.log(arrayExample);
console.log(arrayExample2);

arrayExample2.push(6);

console.log(arrayExample);
console.log(arrayExample2);

console.log([1, 2, 3] == [1, 2, 3]);
console.log([1, 2, 3] === [1, 2, 3]);

console.log(arrayExample == arrayExample2);

// ---

/**
 * function that multiplays two numbers
 * @param {number} a first number
 * @param {number} b second number
 * @returns {number}
 */
function multiple(a, b) {
  return a * b;
}

console.log(multiple(2, 3));
console.log(multiple(2, "3"));

const people = [];

// Callback

function doSomething(callback, a, b) {
  return callback(a, b);
}

console.log(doSomething(add, 2, 3));
