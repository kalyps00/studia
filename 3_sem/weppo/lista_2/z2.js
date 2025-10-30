//użycie operatorów . oraz [] do odwoływania się do składowych obiektu
const car = {
  make: "Honda",
  model: "Accord",
  year: 2020,
  1: 555,
  obiekt: "VW",
  "[object Object]": "test value",
};
const obiekt = {
  make: "VW",
};
console.log(car.make);

console.log(car["make"]);
console.log("\n");

console.log(car[1]); //Konswersja toString 1 -> '1'
console.log(car[obiekt] + "\n"); // konwersja uzywajac .toString() obiekt -> [object Object]
//Js automatycznie konwertuje argument w [] na string

//użycie argumentów innego typu niż number dla operatora [] dostępu do tablicy.

const tab = [1, 2, 3, 4];

console.log(tab["1"]); // konwersja na numer '1' -> 1
console.log(tab[car]); // car -> (toString) [object Object] -> (Number) NaN tab[Nan] -> undefined
console.log(tab.length);
tab[car] = 1;
tab["abc"] = 2;
console.log(tab[car]);
console.log(tab);
console.log(tab.length + "\n");

tab.length = 6;
console.log(tab);
console.log(tab.length);
tab.length = 3;
console.log(tab);
//rozszerzenie length tworzy puste miejsca, zmniejszenie ucina elementy ktore są poza length
