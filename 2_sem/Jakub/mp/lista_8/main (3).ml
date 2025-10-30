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
  
let rename_expr e =
  let rec aux env counter = function
  |Let(x,e1,e2) ->
      let new_x = "#" ^ string_of_int counter in
      let e1',counter' = aux env (counter + 1) e1 in
      let e2',counter'' = aux ((x,new_x):: env) (counter') e2 in
      (Let (new_x,e1',e2'),counter'')
  | Var x ->
    (try (Var (List.assoc x env),counter)
  with Not_found -> (Var x,counter))
  | Binop (op,e1,e2) ->
    let e1',counter' = aux env counter e1 in
    let e2',counter'' = aux env counter' e2 in
    (Binop (op,e1',e2'),counter'')
  | Int i -> (Int i,counter)
  | Bool b -> (Bool b,counter)
  | If (c,t,e) ->
    let c',counter' = aux env counter c in
    let t',counter'' = aux env counter' t in
    let e',counter''' = aux env counter'' e in
    (If(c',t',e'),counter''')
  in
  let e',_=aux [] 1 e in e'
let interp (s : string) : value =
  eval (parse s)
