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
const addBookToLibrary = (title, author, pages, isAvailable, ratings) => {
  if (typeof title !== "string" || title.length === 0) {
    throw new Error("title must be a non-empty string");
  }
  if (typeof author !== "string" || author.length === 0) {
    throw new Error("author must be a non-empty string");
  }
  if (pages !== "number" && pages <= 0) {
    throw new Error("pages must be a positive number");
  }
  if (typeof isAvailable !== "boolean") {
    throw new Error("isAvailable must be a boolean");
  }
  if (Array.isArray(ratings)) {
    for (let i = 0; i < ratings.length; i++) {
      if (typeof ratings[i] !== "number" || ratings[i] < 0 || ratings[i] > 5) {
        throw new Error("ratings must be an array of numbers between 0 and 5");
      }
    }
  } else {
    throw new Error("ratings must be an array");
  }
  library.push({
    title,
    author,
    pages,
    available: isAvailable,
    ratings,
  });
};
let library = [];

let addBooksToLibrary = (books) => {
  for (let book of books) {
    addBookToLibrary(...book);
  }
};
console.log("Library before adding books:");
console.log(library);

addBooksToLibrary(books);
console.log("\nLibrary after adding books:");
console.log(library);
