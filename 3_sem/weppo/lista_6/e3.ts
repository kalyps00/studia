type Person = { // type alias, nowy typ którym jest obiektem
    name: string,
    surname: string
}
type Animal = {
    name: string,
    species: string
}

type PersonAndAnimal = Person & Animal;
type PersonAndString = Person & string;
type PersonOrAnimal = Person | Animal;
type PersonOrString = Person | string;
type StringAndNumber = string & number;
type StringOrNumber = string | number;

//1
function processPersonAndAnimal(obj: PersonAndAnimal): void {
    console.log(`${obj.name} ${obj.surname} is a ${obj.species}`);
}
processPersonAndAnimal({
    name: "Jan",
    surname: "Kowalski",
    species: "Homo sapiens"
});

//2 niemozliwe bo nie moze byc jednozcesnie obiektem i stringiem 

//3
function processPersonOrAnimal(obj: PersonOrAnimal): void {
    console.log(`Name: ${obj.name}`);
    if ('surname' in obj) {
        console.log(`Person: ${obj.name} ${obj.surname}`);
    } else {
        console.log(`Animal: ${obj.name}, species: ${obj.species}`);
    }
}

processPersonOrAnimal({
    name: "Anna",
    surname: "Nowak"
});

processPersonOrAnimal({
    name: "Burek",
    species: "Pies"
});
//4
function processPersonOrString(input: PersonOrString): void {
    if (typeof input === 'string') {
        console.log(`String: ${input}`);
    } else {
        console.log(`Person: ${input.name} ${input.surname}`);
    }
}
processPersonOrString({
    name: "Piotr",
    surname: "Kowalski"
});
processPersonOrString("Hello World");
//5 niemozliwe bo nie moze byc jednoczesnie string i number

//6
function processStringOrNumber(value: StringOrNumber): void {
    if (typeof value === 'string') {
        console.log(`String: ${value.toUpperCase()}`);
    } else {
        console.log(`Number: ${value * 2}`);
    }
}
processStringOrNumber("typescript");
processStringOrNumber(42);