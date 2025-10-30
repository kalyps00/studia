# Zadanie: Wyzwania (10p)

Rozwiąż poniższe zadania. Dla niektórych z nich zostały dodane funkcje pomagające zweryfikować poprawność rozwiązań. Dla pozostałych, samodzielnie przygotuj prezentację ich poprawności.

## Materiały

Do zadania jak zwykle przydać się może [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide). Dobrym źródłem nauki JavaScriptu jest także [javascript.info](https://javascript.info/).

Na tej liście szczególnie przydatne mogą okazać się pojęcia `hoistingu`, [Keyed collections](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects#keyed_collections), [Exception handling statements](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Control_flow_and_error_handling#exception_handling_statements)

## Wyzwanie 1

Wywołanie poniższego kodu wyrzuca błąd. Popraw ją, nie zmieniając kolejności linii.

```js
console.log(capitalize("alice"));

const capitalize = (str) => {
  return str.charAt(0).toUpperCase() + str.slice(1);
};
```

## Wyzwanie 2

Używając funkcji `capitalize` z poprzedniego zadania, napisz funkcję `capitalizeSentence` która powiększy pierwszą literę w każdym wyrazie.

   <details>
     <summary>Weryfikacja</summary>

```js
console.log(capitalizeSentence("alice"));
console.log(capitalizeSentence("alice in wonderland"));
```

   </details>

## Wyzwanie 3

Poniższa funkcja służy do generacji unikalnego ID:

```js
const ids = [];

const generateId = () => {
  let id = 0;

  do {
    id++;
  } while (ids.includes(id));

  ids.push(id);
  return id;
};
```

Wywołując poniższy test:

```js
console.time("generateId");

for (let i = 0; i < 3000; i++) {
  generateId();
}

console.timeEnd("generateId");
```

Możemy zauważyć, że funkcji dość długo zajmuje generowanie kolejnych ID.

Popraw funkcję `generateId`, poprzez zmianę struktury danych przechowującą obecnie wykorzystywane ID (i, oczywiście, modyfikując funkcję tak, by wspierała nową strukturę). Nie zmieniaj samego sposobu działania funkcji.

Wykonaj powyższy test by porównać czasy wykonania.

## Wyzwanie 4

Stwórz funkcję, która porówna dwa obiekty. Możesz założyć, że obiekty zawierać będą tylko elementy typu `number`, `string` oraz ewentualnie inne obiekty o tej samej strukturze. Obiekty mogą być jednak dowolnie zagnieżdżone.

   <details>
     <summary>Weryfikacja</summary>

```js
const obj1 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
};

const obj2 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
};

const obj3 = {
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
  name: "Alice",
};

const obj4 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Not Wonderland",
    country: "Fantasy",
  },
};

const obj5 = {
  name: "Alice",
};

console.log("Should be True:", compareObjects(obj1, obj2));
console.log("Should be True:", compareObjects(obj1, obj3));
console.log("Should be False:", compareObjects(obj1, obj4));
console.log("Should be True:", compareObjects(obj2, obj3));
console.log("Should be False:", compareObjects(obj2, obj4));
console.log("Should be False:", compareObjects(obj3, obj4));
console.log("Should be False:", compareObjects(obj1, obj5));
console.log("Should be False:", compareObjects(obj5, obj1));
```

   </details>

## Wyzwanie 5

Dodaj walidację do poniższej funkcji. Funkcja powinna rzucać wyjątkiem, jeśli podane do niej argumenty są niepoprawne.

Warunki:

- `title` powinien być niepustym napisem
- `author` powinien być niepustym napisem
- `pages` powinna być dodatnią liczbą
- `isAvailable` powinno być wartością typu `boolean`
- `ratings` jest tablicą liczb pomiędzy 0 a 5
- `ratings` może być pustą tablicą

```js
let library = [];

const addBookToLibrary = (title, author, pages, isAvailable, ratings) => {
  library.push({
    title,
    author,
    pages,
    available: isAvailable,
    ratings,
  });
};
```

## Wyzwanie 6

Stwórz funkcję `testAddingBooks` która zweryfikuje poprawność twojego rozwiązania poprzedniego wyzwania. Funkcja powinna przyjąć tablicę testów, a każdy test powinien być obiektem z dwoma polami: `testCase`, będący tablicą argumentów, oraz `shouldFail`, będącą wartością boolowską, mówiącą o tym czy test powinien rzucić wyjątkiem czy nie. Przykładowa struktura:

```js
const testCases = [
  { testCase: ["", "Author", 200, true, []], shouldFail: true },
  { testCase: ["Title", "", 200, true, []], shouldFail: true },
  { testCase: ["Title", "Author", -1, true, []], shouldFail: true },
  { testCase: ["Title", "Author", 200, "yes", []], shouldFail: true },
  { testCase: ["Title", "Author", 200, true, [1, 2, 3, 6]], shouldFail: true },
  {
    testCase: ["Title", "Author", 200, true, [1, 2, 3, "yes"]],
    shouldFail: true,
  },
  { testCase: ["Title", "Author", 200, true, [1, 2, 3, {}]], shouldFail: true },
  { testCase: ["Title", "Author", 200, true, []], shouldFail: false },
  { testCase: ["Title", "Author", 200, true, [1, 2, 3]], shouldFail: false },
  { testCase: ["Title", "Author", 200, true, [1, 2, 3, 4]], shouldFail: false },
  {
    testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
    shouldFail: false,
  },
  {
    testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
    shouldFail: false,
  },
];
```

Działanie funkcji:

- Dla każdego przypadku testowego, wywołaj funkcję `addBookToLibrary`, z argumentami z `testCase`.
- Jeśli funkcja rzuca wyjątkiem, a `shouldFail` ma wartość `false`, wypisz `Test failed`
- Jeśli funkcja nie rzuca wyjątkiem, a `shouldFail` ma wartość `false`, wypisz `Test passed`
- Jeśli funkcja rzuca wyjątkiem a `shouldFail` ma wartość `true`, wypisz `Test passed`
- Jeśli funkcja nie rzuca wyjątkiem a `shouldFail` ma wartość `true`, wypisz `Test failed`
- Dla każdego z przypadków, wypisz jaki był przypadek testowy, a w przypadku gdy funkcja wyrzuciła błąd, dodatkowo dodaj też wiadomość błędu.

Wywołaj funkcję z podanym wyżej argumentem, i w ten sposób zweryfikuj poprawność rozwiązania z wyzwania 5.

## Wyzwanie 7

W tym wyzwaniu będziesz wykorzystywać funkcję z Wyzwania 5. Możesz wykorzystać funkcję bez obsługi błędów, jeśli nie udało ci się zrobić Wyzwania 5.

Stwórz funkcję `addBooksToLibrary` która przyjmuje tablicę tablic argumentów, i z pomocą funkcji `addBookToLibrary` doda je wszystkie do biblioteki.

   <details>
     <summary>Weryfikacja</summary>

```js
const books = [
  ["Alice in Wonderland", "Lewis Carroll", 200, true, [1, 2, 3]],
  ["1984", "George Orwell", 300, true, [4, 5]],
  ["The Great Gatsby", "F. Scott Fitzgerald", 150, true, [3, 4]],
  ["To Kill a Mockingbird", "Harper Lee", 250, true, [2, 3]],
  ["The Catcher in the Rye", "J.D. Salinger", 200, true, [1, 2]],
  ["The Hobbit", "J.R.R. Tolkien", 300, true, [4, 5]],
  ["Fahrenheit 451", "Ray Bradbury", 200, true, [3, 4]],
  ["Brave New World", "Aldous Huxley", 250, true, [2, 3]],
  ["The Alchemist", "Paulo Coelho", 200, true, [1, 2]],
  ["The Picture of Dorian Gray", "Oscar Wilde", 300, true, [4, 5]],
];

addBooksToLibrary(books);
console.log(library);
```

   </details>
