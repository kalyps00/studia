const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("Jak masz na imię? ", (name) => {
  console.log(`Witaj ${name}`);
  rl.close();
});
