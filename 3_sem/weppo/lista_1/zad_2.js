for (let n = 1; n <= 100000; n++) {
  let digits = String(n).split("");
  let suma = 0;
  let dzieliWszystkie = true;
  for (let d of digits) {
    let cyfra = Number(d);
    suma += cyfra;
    if (cyfra === 0 || n % cyfra !== 0) {
      dzieliWszystkie = false;
      break;
    }
  }
  if (dzieliWszystkie && n % suma === 0) {
    console.log(n);
  }
}
