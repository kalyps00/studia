type AExclude<T,U> = T extends U? never : T;
type new123 = AExclude<('a'|'b'|'c'),'a' | 'b'>