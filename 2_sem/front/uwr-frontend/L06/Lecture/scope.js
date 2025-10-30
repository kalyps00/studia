// Scope globalny
let var1 = "var1";
const var2 = "var2";
var var3 = "var3";

console.log(var1, var2, var3);

// Scope blokowy
// let, const mają
// var nie ma
if (true) {
  console.log(var1, var2, var3);

  let var4 = "var4";
  const var5 = "var5";
  var var6 = "var6";

  console.log(var4, var5, var6);
}

console.log(var6);

// Scope funkcyjny
// let, const i var mają
(function test() {
  console.log(var1, var2, var3);
  console.log(var6);

  let var7 = "var7";
  const var8 = "var8";
  var var9 = "var9";

  // Zmienna globalna
  var10 = "var10";

  console.log(var7, var8, var9);
  console.log(var10);
})();
// IIFE
// Immediately Invoked Function Expression

console.log(var10);

function test() {
  var11 = "var11";
}

test();
console.log(var11);
