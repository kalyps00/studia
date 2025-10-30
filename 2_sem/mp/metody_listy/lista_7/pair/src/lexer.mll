{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let number = '-'? digit+
let char = ['a'-'z' 'A'-'Z' '_']
let ident = char(char|digit)*

rule read =
    parse
    | white { read lexbuf }
    | "*" { TIMES }
    | "+" { PLUS }
    | "-" { MINUS }
    | "/" { DIV }
    | "&&" { AND }
    | "||" { OR }
    | "=" { EQ }
    | "<=" { LEQ }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "->" { ARR }
    | "if" { IF }
    | "then" { THEN }
    | "let" { LET }
    | "in" { IN }
    | "else" { ELSE }
    | "true" { BOOL true }
    | "false" { BOOL false }
    | "," { COMMA }
    | "()" { UNIT }
    | "fst" { FST }
    | "snd" { SND }
    | "match" { MATCH }
    | "with" { WITH }
    | "number?" { IS_NUMBER } (* 2 *)
    | "boolean?" { IS_BOOLEAN }(* 2 *)
    | "pair?" { IS_PAIR }(* 2 *)
    | "unit?" { IS_UNIT }(* 2 *)
    | "[" { LBRACKET } (* zad3 *)
    | "]" { RBRACKET }(* zad3 *)
    | ";" { SEMICOLON } (* zad3 *)
    | "fold" { FOLD } (* zad4 *)
    | "and" {AND_S} (* zad4 *)
    | number { INT ( int_of_string (Lexing.lexeme lexbuf)) }
    | ident { IDENT (Lexing.lexeme lexbuf) }
    | eof { EOF }
