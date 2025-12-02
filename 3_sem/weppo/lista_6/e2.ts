function FibRec(n : number) : number{
  if (n == 1 || n == 2) {
    return 1;
  }
  return FibRec(n - 1) + FibRec(n - 2);
}

function memoize(fn : (n: number) => number) : (n: number) => number {
  let cache : {[key: number]: number} = {};
  return function (n : number) : number {
    if (n in cache) {
      return cache[n];
    } else {
      var result = fn(n);
      cache[n] = result;
      return result;
    }
  };
}

const memofib = memoize(FibRec);

console.log(memofib(40));
console.log(memofib(40));