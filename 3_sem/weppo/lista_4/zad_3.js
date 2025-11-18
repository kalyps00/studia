function Person(name) {
  this.name = name;
}
Person.prototype.sayHello = function () {
  console.log("Hello, I'm " + this.name);
};

function Worker(name, job) {
  Person.call(this, name);
  this.job = job;
}

//Worker.prototype = Person.prototype /zle bo worker.prototype i person.prototype maja to samo miejsce w pamieci wiec modyfikuja sie oba obiekty
function Worker1(name, job) {
  Person.call(this, name);
  this.job = job;
}
Worker1.prototype = Person.prototype;
Worker1.prototype.work = function () {
  console.log("Working...");
};

var p1 = new Person("Test_person");
p1.work(); // person nie ma metody work
console.log("--------------");

// Worker.prototype = new Person()
// Wywołanie konstruktora bez parametrów może prowadzić do problemów:
// - Konstruktor nie tylko dziedziczy metody, ale także inicjalizuje właściwości (np. person.name),
//   które i tak zostaną nadpisane przez konstruktor Worker.
// - Jeśli konstruktor Person wykonuje dodatkowe operacje (np. logi, zapisy do plików),
//   to zostaną one niepotrzebnie wywołane.
// - Tworzymy instancję obiektu tylko po to, aby użyć jej jako prototypu, co marnuje pamięć.
// - Aby stworzyć łańcuch prototypów, nie musimy tworzyć instancji obiektu.
function Worker2(name, job) {
  Person.call(this, name);
  this.job = job;
}
Worker2.prototype = new Person();
console.log(Worker2.prototype.name);
console.log("--------------");
// Object.create(person.prototype) //nie ma takiej sytuacji jak w 1. ani w 2.
function Worker3(name, job) {
  Person.call(this, name);
  this.job = job;
}
Worker3.prototype = Object.create(Person.prototype); //nie wplywa na Person.prorotype i nie wywoluje konstruktora Person
Worker3.prototype.work = function () {
  console.log("Working as " + this.job);
};

var w = new Worker3("Mariusz", "spawacz");
w.sayHello();
w.work();
console.log(w.name);
