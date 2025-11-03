// Memo iterative
function fib_mem(n, mem) {
  mem[0] = 0;
  mem[1] = 1;
  if (n in mem) return mem[n];
  else return (mem[n] = fib_mem(n - 2, mem) + fib_mem(n - 1, mem));
}

// naive
function FibRec(n) {
  if (n == 1 || n == 2) {
    return 1;
  }
  return FibRec(n - 1) + FibRec(n - 2);
}

function memoize(fn) {
  var cache = {};
  return function (n) {
    if (n in cache) {
      return cache[n];
    } else {
      var result = fn(n);
      cache[n] = result;
      return result;
    }
  };
}

const memofib2 = memoize(FibRec);

const memofib41 = memoize(FibRec);
// cache z wynikiem 41
memofib41(41);

function timeAndLog(label, fn, arg) {
  console.time(label);
  const result = fn(arg);
  console.timeEnd(label);
  /* console.log(`${label} -> result: ${result}\n`); */
  return result;
}

timeAndLog("fib_mem(41)", (n) => fib_mem(n, []), 41);
timeAndLog("memofib(41) cached", memofib41, 41);
timeAndLog("FibRec(41)", FibRec, 41);

console.log("--------------------------------------------------");

timeAndLog("fib_mem(40)", (n) => fib_mem(n, []), 40);
timeAndLog("FibRec(40)", FibRec, 40);

// new cache
const memofib40 = memoize(FibRec);
timeAndLog("memofib(40)", memofib40, 40);
