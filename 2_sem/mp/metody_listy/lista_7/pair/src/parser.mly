%{
open Ast
%}

%token <bool> BOOL
%token <int> INT
%token <string> IDENT
%token IF
%token THEN
%token ELSE
%token LET
%token IN
%token PLUS
%token MINUS
%token TIMES
%token DIV
%token AND
%token OR
%token EQ
%token LEQ
%token LPAREN
%token RPAREN
%token EOF
%token COMMA
%token UNIT
%token FST
%token SND
%token MATCH
%token WITH
%token ARR
%token IS_NUMBER /* zad2 */
%token IS_BOOLEAN
%token IS_UNIT
%token IS_PAIR /* zad2 */
%token LBRACKET /* zad3 */
%token RBRACKET
%token SEMICOLON /* zad3 */
%token FOLD /* zad4 */
%token AND_S /* zad4 */

%start <Ast.expr> main

%left AND OR
%nonassoc EQ LEQ
%left PLUS MINUS
%left TIMES DIV

%%

main:
    | e = mexpr; EOF { e }
    ;

mexpr:
    | IF; e1 = mexpr; THEN; e2 = mexpr; ELSE; e3 = mexpr
        { If(e1, e2, e3) }
    | LET; x = IDENT; EQ; e1 = mexpr; IN; e2 = mexpr
        { Let(x, e1, e2) }
    | MATCH; e1 = mexpr; WITH; LPAREN; x = IDENT; COMMA; y = IDENT; RPAREN; ARR; e2 = mexpr
        { Match(e1, x, y, e2) }
    | e = expr
        { e }
    ;

expr:
    | i = INT { Int i }
    | b = BOOL { Bool b }
    | x = IDENT { Var x }
    | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
    | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
    | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
    | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
    | e1 = expr; AND; e2 = expr { Binop(And, e1, e2) }
    | e1 = expr; OR; e2 = expr { Binop(Or, e1, e2) }
    | e1 = expr; EQ; e2 = expr { Binop(Eq, e1, e2) }
    | e1 = expr; LEQ; e2 = expr { Binop(Leq, e1, e2) }
    | LPAREN; e1 = mexpr; COMMA; e2 = mexpr; RPAREN { Pair (e1,e2) }
    | UNIT { Unit }
    | FST; e = expr { Fst e }
    | SND; e = expr { Snd e }
    | LPAREN; e = mexpr; RPAREN { e }
    | IS_NUMBER; e = expr { Is_Number e } /* zad2 v*/
    | IS_BOOLEAN; e = expr { Is_Boolean e }
    | IS_UNIT; e = expr { Is_Unit e }
    | IS_PAIR; e = expr { Is_Pair e }/* zad2  ^ */
    | LBRACKET; elems= list_elements; RBRACKET { elems } /* zad3 */
    | FOLD; e1=expr; WITH; LPAREN; x=IDENT; COMMA; acc=IDENT; RPAREN;ARR; e2=expr; AND_S e3=expr {Fold(e1, x, acc, e2, e3)} /* zad4 */
    ;
list_elements:
    |e = expr; SEMICOLON; rest = list_elements { Pair (e, rest) } /* zad 3 */
    |e = expr {Pair (e, Unit)}
