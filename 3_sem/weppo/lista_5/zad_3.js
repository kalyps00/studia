const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const randomNumber = Math.floor(Math.random() * 101);

function ask() {
  rl.question("Zgadnij liczbę (0-100): ", (input) => {
    const guess = Number(input);
    if (guess === randomNumber) {
      console.log("To jest właśnie ta liczba");
      rl.close();
    } else if (guess < randomNumber) {
      console.log("Moja liczba jest większa");
      ask();
    } else {
      console.log("Moja liczba jest mniejsza");
      ask();
    }
  });
}

ask();
