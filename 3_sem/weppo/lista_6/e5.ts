type User = {
    name: string;
    age: number;
    occupation: string;
}
type Admin = {
    name: string;
    age: number;
    role: string;
}
type Person = User | Admin;

const persons: Person[] = [
    {
    name: 'Jan Kowalski',
    age: 17,
    occupation: 'Student'
    },
    {
    name: 'Tomasz Malinowski',
    age: 20,
    role: 'Administrator'
    }
];



function isAdmin(person: Person) : boolean {
    if('role' in person)
    {
        return true;
    }
    return false;
}
function isUser(person: Person) : boolean {
    if('occupation' in person)
    {
        return true;
    }
    return false;
}


function logPerson(person: Person) {
    let additionalInformation: string = '';
    if (isAdmin(person)) {
        additionalInformation = person.role;
    }
    if (isUser(person)) {
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

logPerson(persons[0]);
logPerson(persons[1]);