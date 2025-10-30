const obj1 = {
  name: "John",
  surname: "Doe",
  getFullName: function () {
    return this.name + " " + this.surname;
  },
};

console.log(obj1.getFullName());

obj1.name = "Alice";

console.log(obj1.getFullName());

function getFullName() {
  return this.name + " " + this.surname;
}

const obj2 = {
  name: "Jane",
  surname: "Smith",
  getFullName: getFullName,
};

const obj3 = {
  name: "Bob",
  surname: "Brown",
  getFullName: obj1.getFullName,
};

console.log(obj2.getFullName());
console.log(obj3.getFullName());
console.log(getFullName());
console.log(obj3.getFullName());

const obj4 = {
  name: "Charlie",
  surname: "Johnson",
  greetInOneSecond: function () {
    setTimeout(function () {
      console.log("Hello, " + this.name);
    }, 1000);
  },
};

//console.log(obj4.greetInOneSecond());

const obj5 = {
  name: "Charlie",
  surname: "Johnson",
  greetInOneSecond: function () {
    setTimeout(() => {
      console.log("Hello2, " + this.name);
    }, 1000);
  },
};

//console.log(obj5.greetInOneSecond());

const obj6 = {
  name: "Charlie",
  surname: "Johnson",
  getFullName: () => {
    console.log("----------");
    return this.name + " " + this.surname;
  },
};

console.log(obj6.getFullName());
