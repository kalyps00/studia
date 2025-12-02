const tesla = ['tesla', 'model 3', 'model X', 'model Y'] as const

type Length<T extends readonly any[]> = T['length']

type L1 = Length<typeof tesla>


