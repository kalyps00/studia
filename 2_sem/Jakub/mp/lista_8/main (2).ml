open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

let rec subst (x : ident) (s : expr) (e : expr) : expr =
  match e with
  | Binop (op, e1, e2) -> Binop (op, subst x s e1, subst x s e2)
  | If (b, t, e) -> If (subst x s b, subst x s t, subst x s e)
  | Var y -> if x = y then s else e
  | Let (y, e1, e2) ->
      Let (y, subst x s e1, if x = y then e2 else subst x s e2)
  | _ -> e

let reify (v : value) : expr =
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b

let rec eval (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval e1) (eval e2)
  | If (b, t, e) ->
      (match eval b with
           | VBool true -> eval t
           | VBool false -> eval e
           | _ -> failwith "type error")
  | Let (x, e1, e2) ->
      eval (subst x (reify (eval e1)) e2)
  | Var x -> failwith ("unknown var " ^ x)

let alpha_equiv e1 e2 = 
  let rec compare env1 env2 e1 e2 =
    (match (e1,e2) with
    | Int i1,Int i2 -> i1=i2
    | Bool b1,Bool b2 -> b1=b2
    | Var x,Var y ->
      (try (List.assoc x env1 = y) && (List.assoc y env2 = x)
    with Not_found -> x=y)
    | Binop (op1,a1,b1),Binop(op2,a2,b2) ->
      op1=op2 && compare env1 env2 a1 a2 && compare env1 env2 b1 b2
    | If(c1,t1,e1),If(c2,t2,e2) ->
      compare env1 env2 c1 c2 && compare env1 env2 t1 t2 && compare env1 env2 e1 e2
    | Let (x,e1a,e1b),Let(y,e2a,e2b) ->
      compare env1 env2 e1a e2a && compare ((x,y)::env1) ((y,x)::env2) e1b e2b
    | _ -> false)
    in compare [] [] e1 e2 (*rozne konstrukcje*)
let interp (s : string) : value =
  eval (parse s)
