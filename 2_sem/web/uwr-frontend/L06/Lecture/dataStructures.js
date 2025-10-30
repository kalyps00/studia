const array1 = [1, 2, 3, 4, 5];
const object1 = {
  name: "John",
  age: 30,
};

const map1 = new Map();

console.log(map1);

map1.set("name", "John");
map1.set("age", 30);

console.log(map1);

/* const object2 = {};

console.time("object");

for (let i = 0; i < 1000000; i++) {
  let randomString = Math.random().toString(36).substring(2, 15);
  object2[randomString] = i;
}

console.timeEnd("object");

console.time("map");

for (let i = 0; i < 1000000; i++) {
  let randomString = Math.random().toString(36).substring(2, 15);
  map1.set(randomString, i);
}

console.timeEnd("map");
 */
console.log(map1.size);

const set1 = new Set();
set1.add("John");
set1.add("Doe");

console.log(set1);
set1.add("John");
set1.add("John");
set1.add("John");
set1.add("John");
set1.add("John");
set1.add("John");
console.log(set1);
