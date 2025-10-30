// deklaracja
let variable1;

// inicjalizacja/przypisanie
variable1 = "variable1";

// użycie
console.log(variable1);

// ------------ Start pliku -----
// Hoistowanie bez wartości/hoisting deklaracji
var variable2;

console.log(variable2);
variable2 = "variable2";
console.log(variable2);

//console.log(variable3);
// Hoistowanie "zanieczyszcające" scope
const variable3 = "variable3";
console.log(variable3);

hoisting();

// Hoistowanie z wartością
function hoisting() {
  console.log("Hello World");
}

hoisting();

//function1();

const function1 = function () {
  console.log("Hello World");
};

const variable4 = "variable4";

if (true) {
  //console.log(variable4);
  const variable4 = "variable4";
  console.log(variable4);
}

function test2() {
  const variable4 = "variable4";
}

const array = [];

array.push("Hello");

console.log(array);
