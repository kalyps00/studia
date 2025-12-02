type Unshift<T extends readonly any[],U> = [U,...T]
type Result123 = Unshift<[1, 2], 0> // [0, 1, 2]