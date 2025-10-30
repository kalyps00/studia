type bop = Add | Sub | Mult | Div | Pow

type expr = 
    | Float of float
    | Binop of bop * expr * expr
    | Log of expr
