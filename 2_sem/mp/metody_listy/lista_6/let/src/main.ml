open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool
  (* zad 3 *)
  | VUnit
  (* zad 4 *)
  | VPair of value * value

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

let rec reify (v : value) : expr =(* rec zad 4 *)
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b
  | VUnit -> Unit (* zad 3 *)
  | VPair (v1, v2) -> Pair (reify v1, reify v2) (* zad 4 *)

let rec eval (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Unit -> VUnit (* zad 3 *)
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
  (* zad 4 *)
  | Pair (e1, e2) -> VPair (eval e1, eval e2)
  | Fst e -> (match eval e with
      | VPair (v1, _) -> v1
      | _ -> failwith "type error")
  | Snd e -> (match eval e with
    | VPair (_, v2) -> v2
    | _ -> failwith "type error")
  (* zad 7 *)
  | Sum (x,n,m,k) -> 
    let n_val = match eval n with
      | VInt i -> i
      | _ -> failwith "type error"
    in
    let m_val = match eval m with
      | VInt i -> i
      | _ -> failwith "type error"
    in
    let rec sum acc i = 
      if i> m_val then acc
      else let k_subst = subst x (Int i) k in
      match eval k_subst with
      | VInt v -> sum (acc + v) (i + 1)
      | _ -> failwith "type error"
    in
    VInt (sum 0 n_val)


let interp (s : string) : value =
  eval (parse s)

(* zad1 *)(* 
  let closed ( e : expr ) : bool = 
  let rec aux (e : expr) (xs : ident list) : bool =
    match e with
    | Int _ -> true
    | Bool _ -> true
    | Var x -> List.mem x xs
    | Binop (_, e1, e2) -> aux e1 xs && aux e2 xs
    | If (b, t, e) -> aux b xs && aux t xs && aux e xs
    | Let (x, e1, e2) ->
        aux e1 xs && aux e2 (x :: xs)
  in
  aux e [] *)

  