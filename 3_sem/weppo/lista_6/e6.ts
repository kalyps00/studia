//Extract i Exclude

type Colors = 
    | "burgundy"
    | "navy"
    | "cerulean"
    | [number,number,number]
    | {red : number; green: number; blue: number}

type StringColors = Extract<Colors,string>
type NonStringColor = Exclude <Colors,string>


//Partial,Record,Required,Readonly
//zmienia wszystkie properties w obiekcie na opcjonalne wiec mozemy uzywac pojedynczych
interface Point {
    x: number;
    y: number;
}
let partialPoint: Partial<Point> = {};
partialPoint.x = 10;

//Required robi dokładnie na odwrót 
interface Car {
    make: string;
    model : string;
    mileage?: number;
}

let myCar: Required<Car> = {
    make: 'Ford',
    model: 'Focus',
    mileage: 150000 // program wymaga teraz 'mileage' pomimo ustawienia tego na opcjonalne w interfejsie
}

//Record pozwala nam jednolinijkowcem stworzyc obiekt postaci <key,value>

const ages: Record<string,number> = {
    'Ala' : 21,
    'Jakub' : 20
};

//Readonly uniemozliwia edycje zmiennej property w obiekcie

let myCar2 : Readonly<Car> = {
    make: 'Ford',
    model: 'Focus',
    mileage: 150000
}
myCar2.mileage = 15000 //tutaj mamy bład


//Pick, Omit
interface Person1 {
    name : string;
    age: number;
}
//mozemy wyodrebnic tylko te property ktore chcemy
const PersonsName: Pick<Person1, 'name'> = {
    name: 'Ala'
}

//Omit na odwrót

const PersonsName2: Omit<Person1, 'age'> = {
    name: 'Ala'
}

//typy Indeksowane
type Age = Person1['age'];