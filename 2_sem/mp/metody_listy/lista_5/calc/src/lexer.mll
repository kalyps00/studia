{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let number = '-'? digit+ '.'? digit*


rule read =
    parse
    | white { read lexbuf }
    | "*" { TIMES }
    | "**" { POW } 
    | "+" { PLUS }
    | "-" { MINUS }
    | "/" { DIV }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "log" { LOG } 
    | "e" { E }
    | number { FLOAT ( float_of_string (Lexing.lexeme lexbuf)) }
    | eof { EOF }
