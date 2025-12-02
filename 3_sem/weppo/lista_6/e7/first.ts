type arr1 = ['a', 'b', 'c']
type First<T extends any[]> = T extends [] ? never : T[0]


type first1 = First<['a','b','c']>