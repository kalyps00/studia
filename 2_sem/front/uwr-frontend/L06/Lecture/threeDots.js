const array1 = ["one", "two", "three", "four", "five"];

//const first = array1[0];

const [first] = array1;

console.log(first);

const [one, ...rest] = array1;

console.log(one);
console.log(rest);

const object1 = {
  name: "John",
  age: 30,
  city: "New York",
  country: "USA",
  hobbies: ["reading", "traveling"],
};

const { name: firstName, age, ...rest2 } = object1;

console.log(firstName);
console.log(age);
console.log(rest2);

const array2 = [1, 2, 3, 4, 5];

const array3 = [...array1, ...array2];

console.log(array3);

const copyArray1 = [...array1];

const copyObject1 = { ...object1, hobbies: [...object1.hobbies] };
console.log(copyObject1);
/* copyObject1.name = "Jane";
copyObject1.hobbies.push("sports"); */
console.log(copyObject1);

console.log(object1);

console.log(object1 === copyObject1);
console.log(object1.hobbies === copyObject1.hobbies);

function sum(one, ...args) {
  let total = one;
  for (const arg of args) {
    total += arg;
  }
  return total;
}

console.log(sum(1, 2, 3, 4, 5));
console.log(sum());
