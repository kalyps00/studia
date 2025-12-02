type Concat<T extends readonly any[],U extends readonly any[]> = [...T,...U]

type new1234 = Concat<Concat<[1],[1]>,[2]>