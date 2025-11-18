var p = {
  name: "jan",
};
var q = {
  surname: "kowalski",
};
Object.setPrototypeOf(p, q);
console.log(p.name);
console.log(p.surname);
/* function isOwn(obj, propertyName) {
  if (!(propertyName in obj)) {
    return false;
  }
  let prototype = Object.getPrototypeOf(obj);
  while (prototype) {
    if (propertyName in prototype) {
      return false;
    }
    prototype = Object.getPrototypeOf(prototype);
  }
  return true;
} */
function isOwn(obj, Name) {
  return obj.hasOwnProperty(Name);
}
console.log(isOwn(p, "name"));
console.log(isOwn(p, "surname"));

for (let key in p) {
  if (p.hasOwnProperty(key)) console.log(key);
}
for (let key in p) {
  console.log(key);
}
