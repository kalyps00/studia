const fs = require("fs");

fs.readFile("tekst.txt", "utf8", (err, data) => {
  if (err) {
    console.error("Błąd odczytu pliku:", err);
    return;
  }
  console.log("Zawartość pliku:");
  console.log(data);
});
