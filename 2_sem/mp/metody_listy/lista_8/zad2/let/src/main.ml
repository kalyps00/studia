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

module M = Map.Make(String)
  
let alpha_equiv (e1 : expr) (e2 : expr) : bool =
  let rec alpha_equiv_env (env1 : string M.t) (env2 : string M.t) (e1 : expr) (e2 : expr) : bool =
    match e1, e2 with
    | Int n1, Int n2 -> n1 = n2
    | Bool b1, Bool b2 -> b1 = b2
    | Var x, Var y ->
        (match M.find_opt x env1, M.find_opt y env2 with
         (* obie zmienne są związane*)
         | Some x', Some y' -> x' = y && y' = x
         (* obie zmienne są wolne *)
         | None, None -> x = y
         | _, _ -> false)
    
    | Binop(op1, e1a, e1b), Binop(op2, e2a, e2b) ->
        op1 = op2 && 
        alpha_equiv_env env1 env2 e1a e2a && 
        alpha_equiv_env env1 env2 e1b e2b
    
    | If(c1, t1, e1'), If(c2, t2, e2') ->
        alpha_equiv_env env1 env2 c1 c2 && 
        alpha_equiv_env env1 env2 t1 t2 && 
        alpha_equiv_env env1 env2 e1' e2'
    
    | Let(x1, e1a, e1b), Let(x2, e2a, e2b) ->
        (* wartosci *)
        alpha_equiv_env env1 env2 e1a e2a &&
        (* wyrazenia *)
        alpha_equiv_env 
          (M.add x1 x2 env1) 
          (M.add x2 x1 env2) 
          e1b e2b
    | _, _ -> false
  in
alpha_equiv_env M.empty M.empty e1 e2
(* testowe wyraznia *)
let expr1 = parse "let x = 2 in let y = 5 in x + y";;
let expr2 = parse "let y = 2 in let z = 5 in y + z";;

let interp (s : string) : value =
  eval (parse s)

