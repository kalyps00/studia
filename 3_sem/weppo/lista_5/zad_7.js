const fs = require("fs");
const util = require("util");

//callback
fs.readFile("tekst.txt", "utf8", (err, data) => {
  if (err) {
    console.error("Błąd:", err);
    return;
  }
  console.log("Dane (callback):", data);
});

//wrapper
function readFilePromise_1(path, encoding) {
  return new Promise((resolve, reject) => {
    fs.readFile(path, encoding, (err, data) => {
      if (err) reject(err);
      else resolve(data);
    });
  });
}

//util.promisify
const readFilePromise_2 = util.promisify(fs.readFile);

//fs.promises
const fs1 = require("fs").promises;

//Promise::then
readFilePromise_1("tekst.txt", "utf8")
  .then((data) => console.log("Dane (Promise + then):", data))
  .catch((err) => console.error("Error:", err));

// async/await
async function readFileNew() {
  try {
    const data = await readFilePromise_1("tekst.txt", "utf8");
    console.log("Dane (async/await):", data);
  } catch (err) {
    console.error("Error:", err);
  }
}

readFileNew();
