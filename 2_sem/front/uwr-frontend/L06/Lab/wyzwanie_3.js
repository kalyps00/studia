const ids = new Set();

const generateId = () => {
  let id = 0;

  do {
    id++;
  } while (ids.has(id)); // includes

  ids.add(id); //push
  return id;
};
console.time("generateId");

for (let i = 0; i < 3000; i++) {
  generateId();
}

console.timeEnd("generateId");
