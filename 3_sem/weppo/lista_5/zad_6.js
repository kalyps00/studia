const fs = require("fs");
const readline = require("readline");

const fileStream = fs.createReadStream("logs.txt");

const rl = readline.createInterface({
  input: fileStream,
  crlfDelay: Infinity,
});

const ipCounter = {};

rl.on("line", (line) => {
  let parts = line.split(/\s+/);
  const ip = parts[1];

  if (ipCounter[ip]) {
    ipCounter[ip]++;
  } else {
    ipCounter[ip] = 1;
  }
});

rl.on("close", () => {
  const top3 = Object.entries(ipCounter)
    .sort((a, b) => b[1] - a[1])
    .slice(0, 3);
  top3.forEach(([ip, count]) => {
    console.log(`${ip}: ${count}`);
  });
});
