let library = [];

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

const testAddingBooks = (tests) => {
  for (let test of tests) {
    const { testCase, shouldFail } = test;
    console.log("\n", testCase);

    try {
      addBookToLibrary(...testCase);
    } catch (error) {
      /*  console.log(error.message); */
      if (shouldFail) console.log("Test passed", "\terror", error.message);
      else console.log("Test failed", "\terror", error.message);
      continue;
    }
    if (shouldFail) {
      console.log("Test failed");
    } else {
      console.log("Test passed");
    }
  }
};
testAddingBooks(testCases);
