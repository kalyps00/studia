%token <float> FLOAT /* int */
%token PLUS
%token MINUS
%token TIMES
%token DIV
%token POW (**)
%token LOG
%token E
%token LPAREN
%token RPAREN
%token EOF

%start <Ast.expr> main

%left PLUS MINUS
%left TIMES DIV
%right POW 
%right LOG 
%%

main:
    | e = expr; EOF { e }
    ;

expr:
    | f = FLOAT { Float f } /* i = INT { Int i} */
    | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
    | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
    | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
    | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
    | e1 = expr; POW; e2 = expr { Binop(Pow, e1, e2) } 
    | LOG; e = expr { Log e } 
    | E { Float (exp 1.0) } (* Stała e *)
    | LPAREN; e = expr; RPAREN { e }
    ;



