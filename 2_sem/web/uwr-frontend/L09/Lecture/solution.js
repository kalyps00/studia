"use strict";
function sub(a, b) {
    return a - b;
}
const a = 5;
const b = "6";
const c = true;
//sub(a, b);
let x;
const y = null;
console.log(x); //undefined
const object = {
    name: "Alice",
    surname: "Young",
    address: {
        city: "New York",
        country: "USA",
    },
};
console.log(object.name); // Alice
const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const arr2 = [object];
const tuple = [1, "Alice"];
// TODO: add type
let something = "hello";
something = 1;
something = {
    asddf: "asdff",
};
const variable = "hello";
const variable2 = 1;
const variable3 = true;
//sub(variable, variable2)
const arr3 = ["Hello", "World"];
//arr3[0] = "asdf"
//arr3[0] = "Hello";
let someValue = "Hello, TypeScript!";
let strLength = someValue.length;
let hello = 1;
hello.length;
console.log(strLength); // Outputs: 18
const phone = 1234567890;
const phone2 = "1234567890";
let obj2 = {
    name: "Alice",
    surname: "Young",
    address: {
        city: "New York",
        country: "USA",
    },
    age: 30,
    phone: "1234567890",
    hello: "Hello",
    hello2: "Hello2",
};
function getProperty(key, obj) {
    return obj[key];
}
function smarterAdd(a, b) {
    let numberA;
    let numberB;
    if (typeof a === "string") {
        numberA = Number(a);
    }
    else {
        numberA = a;
    }
    if (typeof b === "string") {
        numberB = Number(b);
    }
    else {
        numberB = b;
    }
    return numberA + numberB;
}
function isDog(animal) {
    return "bark" in animal;
}
function makeNoise(animal) {
    if (isDog(animal)) {
        animal.bark();
    }
    if ("bark" in animal) {
        animal.bark();
    }
    else {
        animal.meow();
    }
}
function doSomething(a, b) {
    if (a === b) {
        let x = a;
        let y = b;
    }
}
function doSomething2(a, b) {
    if (typeof a === "number" && a === b) {
        let x = a;
        let y = b;
    }
}
var Color;
(function (Color) {
    Color["Red"] = "red";
    Color["Green"] = "green";
    Color["Blue"] = "blue";
})(Color || (Color = {}));
Color.Blue;
