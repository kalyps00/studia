function fibIter(n) {
  let a = 0,
    b = 1;
  for (let i = 2; i <= n; i++) {
    [a, b] = [b, a + b];
  }
  return n === 0 ? 0 : b;
}

function fibRec(n) {
  if (n <= 1) return n;
  return fibRec(n - 1) + fibRec(n - 2);
}

console.log("n\tIteracyjnie\tRekurencyjnie");
for (let n = 10; n <= 40; n += 5) {
  console.time("iter");
  let fi = fibIter(n);
  console.timeEnd("iter");
  console.time("rek");
  let fr = fibRec(n);
  console.timeEnd("rek");
  console.log(`${n}\t${fi}\t\t${fr}`);
}
