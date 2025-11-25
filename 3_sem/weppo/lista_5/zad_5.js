const https = require("https");

https
  .get("https://ii.uni.wroc.pl/", (res) => {
    let data = "";
    res.on("data", (chunk) => {
      data += chunk;
    });
    res.on("end", () => {
      console.log("Zawartość zasobu (klasycznie):");
      console.log(data);
    });
  })
  .on("error", (err) => {
    console.error("Błąd:", err);
  });

function fetchUrl(url) {
  return new Promise((resolve, reject) => {
    https
      .get(url, (res) => {
        let data = "";
        res.on("data", (chunk) => {
          data += chunk;
        });
        res.on("end", () => {
          resolve(data);
        });
      })
      .on("error", (err) => {
        reject(err);
      });
  });
}

fetchUrl("https://ii.uni.wroc.pl/")
  .then((data) => {
    console.log("Zawartość zasobu (promise):");
    console.log(data);
  })
  .catch((err) => {
    console.error("Błąd:", err);
  });
