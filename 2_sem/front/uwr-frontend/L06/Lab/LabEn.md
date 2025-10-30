# Task: Challenges (10p)

Solve the following challenges. For some of them, helper functions have been provided to verify the correctness of the solutions. For the others, prepare your own validation to confirm correctness.

## Resources

As usual, [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide) can be helpful for this task. A good learning resource for JavaScript is also [javascript.info](https://javascript.info/).

The following concepts might be particularly useful: `hoisting`, [Keyed collections](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects#keyed_collections), [Exception handling statements](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Control_flow_and_error_handling#exception_handling_statements)

## Challenge 1

Calling the following code results in an error. Fix it without changing the order of the lines.

```js
console.log(capitalize("alice"));

const capitalize = (str) => {
  return str.charAt(0).toUpperCase() + str.slice(1);
};
```

## Challenge 2

Using the capitalize function from the previous challenge, write a function capitalizeSentence that capitalizes the first letter of every word.

   <details>
     <summary>Verification</summary>

```js
console.log(capitalizeSentence("alice"));
console.log(capitalizeSentence("alice in wonderland"));
```

   </details>

## Challenge 3

The following function generates a unique ID:

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

Running the following test:

```js
console.time("generateId");

for (let i = 0; i < 3000; i++) {
  generateId();
}

console.timeEnd("generateId");
```

We can notice that it takes quite a long time to generate the next IDs.

Improve the `generateId` function by changing the data structure that stores currently used IDs (and, of course, modifying the function to support the new structure). Do not change the core functionality of the function.

Run the above test to compare execution times.

## Challenge 4

Create a function that compares two objects. You can assume that the objects will only contain elements of type `number`, `string`, and possibly other objects with the same structure. However, the objects may be arbitrarily nested.

   <details>
     <summary>Verification</summary>

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

## Challenge 5

Add validation to the following function. The function should throw an exception if the provided arguments are incorrect.

Warunki:

- `title` should be a non-empty string
- `author` should be a non-empty string
- `pages` should be a positive number
- `isAvailable` should be a boolean value
- `ratings` is an array of numbers between 0 and 5
- `ratings` can be an empty array

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

## Challenge 6

Create the function `testAddingBooks` which will verify the correctness of your solution from the previous challenge. The function should accept an array of test cases, where each test case is an object with two fields: `testCas`e, an array of arguments, and `shouldFail`, a boolean indicating whether the test should throw an exception.

Example structure:

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

Function behavior:

- For each test case, call addBookToLibrary with the arguments from testCase.
- If the function throws an exception and shouldFail is false, print Test failed.
- If the function does not throw an exception and shouldFail is false, print Test passed.
- If the function throws an exception and shouldFail is true, print Test passed.
- If the function does not throw an exception and shouldFail is true, print Test failed.
- For each case, print the test case, and in case the function threw an error, also print the error message.

Call the function with the provided argument to verify the correctness of the solution from Challenge 5.

## Challenge 7

In this challenge, you will use the function from Challenge 5. You can use the function without error handling if you didn't manage to complete Challenge 5.

Create the function `addBooksToLibrary` which accepts an array of argument arrays, and using the `addBookToLibrary` function, adds them all to the library.

   <details>
     <summary>Verification</summary>

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
