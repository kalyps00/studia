type Push <T extends readonly any[],U>  = [...T,U]

type Result = Push<[1, 2], '3'>