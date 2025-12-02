type Includes<T extends readonly any[],U> = T extends [infer head,...infer tail]? U extends head?  true : Includes<tail,U> : false

type isPillarMen = Includes<['Kars', 'Esidisi', 'Wamuu', 'Santana'], 'Santana'>
