function divisors_imp(n) {
  var divisors = [];
  for (var i = 2; i <= Math.sqrt(n); i++) {
    while (n % i == 0) {
      divisors.push(i);
      n = n / i;
    }
  }
  if (n > 1) divisors.push(n);
  return divisors;
}
function divisors_func(n, i, acc) {
  if (n == 1) {
    return acc;
  }
  if (n % i == 0) return divisors_func(n / i, i, acc.concat(i));
  else {
    return divisors_func(n, i + 1, acc);
  }
}
var d1 = divisors_imp(10);
var d2 = divisors_func(20, 2, []);

console.log("=== divisors (imperative) ===");
console.log("divisors_imp(10) => [", d1.join(", "), "]");

console.log("=== divisors (functional) ===");
console.log("divisors_func(20) => [", d2.join(", "), "]");
