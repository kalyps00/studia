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

  open Ast
  module M = Map.Make(String)
  
  let rename_expr (e : expr) : expr =
    let rec rename_env (env : string M.t) (path : string) (e : expr) : expr =
      match e with
      | Int n -> Int n
      | Bool b -> Bool b
      
      | Var x ->
          (match M.find_opt x env with
           | Some new_name -> Var new_name
           | None -> Var x) (* wolna *)

      | Binop (op, e1, e2) ->
          Binop (op, 
                 rename_env env (path ^ "L") e1,  
                 rename_env env (path ^ "R") e2)
      
      | If (cond, then_e, else_e) ->
          If (rename_env env (path ^ "Q") cond,
              rename_env env (path ^ "T") then_e,
              rename_env env (path ^ "E") else_e)
      
      | Let (x, e1, e2) ->
          let new_name = "#" ^ path in
          (* Przetwórz podwyrażenie przypisania *)
          let new_e1 = rename_env env (path ^ "L") e1 in
          (* Rozszerz środowisko o nowe mapowanie *)
          let new_env = M.add x new_name env in
          (* Przetwórz ciało let z rozszerzonym środowiskiem *)
          let new_e2 = rename_env new_env (path ^ "R") e2 in
          (* Zbuduj nowe wyrażenie let *)
          Let (new_name, new_e1, new_e2)
    in
  rename_env M.empty "" e
  let rec show_expr = function
  | Int i -> string_of_int i
  | Bool b -> string_of_bool b
  | Var x -> x
  | Binop(Add, e1, e2) -> "(" ^ show_expr e1 ^ " + " ^ show_expr e2 ^ ")"
  | Binop(Sub, e1, e2) -> "(" ^ show_expr e1 ^ " - " ^ show_expr e2 ^ ")"
  | Binop(Mult, e1, e2) -> "(" ^ show_expr e1 ^ " * " ^ show_expr e2 ^ ")"
  | Binop(Div, e1, e2) -> "(" ^ show_expr e1 ^ " / " ^ show_expr e2 ^ ")"
  | Binop(And, e1, e2) -> "(" ^ show_expr e1 ^ " && " ^ show_expr e2 ^ ")"
  | Binop(Or, e1, e2) -> "(" ^ show_expr e1 ^ " || " ^ show_expr e2 ^ ")"
  | Binop(Eq, e1, e2) -> "(" ^ show_expr e1 ^ " = " ^ show_expr e2 ^ ")"
  | Binop(Leq, e1, e2) -> "(" ^ show_expr e1 ^ " <= " ^ show_expr e2 ^ ")"
  | If(e1, e2, e3) -> "if " ^ show_expr e1 ^ " then " ^ show_expr e2 ^ " else " ^ show_expr e3
  | Let(x, e1, e2) -> "let " ^ x ^ " = " ^ show_expr e1 ^ " in " ^ show_expr e2;;

let example = parse "let x = 1 in (let y = 2 in x + y + z) + (let x = x in x)";;
let interp (s : string) : value =
  eval (parse s)
