function isPrime(n) {
  if (n < 2) return false;
  for (let i = 2; i < n; i++) {
    if (n % i === 0) return false;
  }
  return true;
}

const primes3 = [];
for (let i = 2; i <= 100000; i++) {
  if (isPrime(i)) primes3.push(i);
}
console.log("Zadanie 3:", primes3);
 debugger;
