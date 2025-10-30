function sub(a: number, b: number) {
  return a - b;
}

const a: number = 5;
const b: string = "6";
const c: boolean = true;

//sub(a, b);
let x: undefined;

const y: null = null;

console.log(x); //undefined

interface Person {
  name: string | number;
  surname: string;
  address: {
    city: string;
    country: string;
  };
}

const object: Person = {
  name: "Alice",
  surname: "Young",
  address: {
    city: "New York",
    country: "USA",
  },
};

console.log(object.name); // Alice

const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const arr2: Person[] = [object];

const tuple: [number, string] = [1, "Alice"];

// TODO: add type
let something: any = "hello";

something = 1;

something = {
  asddf: "asdff",
};

const variable = "hello";
const variable2 = 1;
const variable3 = true;

//sub(variable, variable2)

const arr3 = ["Hello", "World"] as const;

//arr3[0] = "asdf"
//arr3[0] = "Hello";

let someValue: any = "Hello, TypeScript!";
let strLength: number = (someValue as string).length;

let hello = 1;

(hello as any as string).length;

console.log(strLength); // Outputs: 18

type PersonName = string;

interface Person2 {
  name: PersonName;
  age: number;
}

type Phone = string | number | null | undefined;

const phone: Phone = 1234567890;
const phone2: Phone = "1234567890";

type TypePerson = {
  name: "Alice";
  surname: "Young";
  address: {
    city: "New York";
    country: "USA";
  };
};

interface BetterPerson extends Person {
  name: string;
  age: number;
  phone: Phone;
  hello: string;
  hello2: string;
}

let obj2: BetterPerson = {
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

type BetterTypePerson = TypePerson & {
  age: number;
  phone: Phone;
};

//type PropertiesOfType = "name" | "surname" | "address" | "age" | "phone" | "hello";
type PropertiesOfType = keyof BetterPerson;

type KeysOfAddress = keyof BetterPerson["address"];
type Address = BetterPerson["address"];

function getProperty(key: PropertiesOfType, obj: BetterPerson) {
  return obj[key];
}

function smarterAdd(a: string | number, b: string | number) {
  let numberA;
  let numberB;

  if (typeof a === "string") {
    numberA = Number(a);
  } else {
    numberA = a;
  }

  if (typeof b === "string") {
    numberB = Number(b);
  } else {
    numberB = b;
  }

  return numberA + numberB;
}

interface Animal {
  name: string;
}

interface Dog extends Animal {
  //bark: (a: number) => number;
  bark: () => void;
}

function isDog(animal: Animal): animal is Dog {
  return "bark" in animal;
}

interface Cat extends Animal {
  meow: () => void;
}

interface Fish extends Animal {
  swim: () => void;
}

interface GoldenRetriever extends Animal {
  bark: () => void;
}

function makeNoise(animal: Dog | Cat) {
  if (isDog(animal)) {
    animal.bark();
  }

  if ("bark" in animal) {
    animal.bark();
  } else {
    animal.meow();
  }
}

function doSomething(a: number | string, b: number | boolean) {
  if (a === b) {
    let x = a;
    let y = b;
  }
}

function doSomething2(a: number | string, b: number | string) {
  if (typeof a === "number" && a === b) {
    let x = a;
    let y = b;
  }
}

enum Color {
  Red = "red",
  Green = "green",
  Blue = "blue",
}

const EnumObject = {
  Red: "red",
  Green: "green",
  Blue: "blue",
  Violet: "violet",
} as const;

type ColorType = (typeof EnumObject)[keyof typeof EnumObject];

let color1: Color = Color.Red;

let color2: ColorType = "red";
