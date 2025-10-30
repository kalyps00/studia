function add(a, b) {
  if (typeof a !== "number" || typeof b !== "number") {
    throw new Error("Both arguments must be numbers");
  }

  return a + b;
}

console.log(add(2, 3));
console.log(add(3, 2));
//console.log(add(2, "3"));

function mult(a, b) {
  try {
    let multValue = 0;
    for (let i = 0; i < b; i++) {
      multValue = add(multValue, a);
    }

    return multValue;
  } catch (error) {
    console.error("An error occurred in mult function: ", error.message);
    throw error;
  } finally {
    console.log("Here we are!");
  }

  console.log("Here too!");
}

try {
  console.log(mult(2, 3));
  console.log(mult(3, 2));
  console.log(mult("2", 3));
  console.log("Here!");
} catch (error) {
  console.error("An error occurred: ", error.message);
}

console.log("Rest of the program");
