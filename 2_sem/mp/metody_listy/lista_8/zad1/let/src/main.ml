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


(* Środowisko mapujące identyfikatory na wyrażenia *)
module EM = Map.Make(String)
type env_expr = expr EM.t

(* Główna funkcja do propagacji stałych w środowisku *)
let rec cp_env (env : env_expr) (e : expr) : expr =
  match e with
  | Int i -> Int i
  | Bool b -> Bool b
  (* Dla zmiennych, zwracamy ich wartość z środowiska, jeśli jest dostępna *)
  | Var x -> 
      (match EM.find_opt x env with
       | Some e' -> e'
       | None -> Var x)
  
  (* Dla operacji binarnych, próbujemy uprościć operandy a potem całą operację *)
  | Binop (op, e1, e2) ->
      let e1' = cp_env env e1 in
      let e2' = cp_env env e2 in
      (match op, e1', e2' with
       | Add, Int n1, Int n2 -> Int (n1 + n2)
       | Sub, Int n1, Int n2 -> Int (n1 - n2)
       | Mult, Int n1, Int n2 -> Int (n1 * n2)
       | Div, Int n1, Int n2 -> Int (n1 / n2)
       | And, Bool b1, Bool b2 -> Bool (b1 && b2)
       | Or, Bool b1, Bool b2 -> Bool (b1 || b2)
       | Eq, Int n1, Int n2 -> Bool (n1 = n2)
       | Eq, Bool b1, Bool b2 -> Bool (b1 = b2)
       | Leq, Int n1, Int n2 -> Bool (n1 <= n2)
       | _, _, _ -> Binop(op, e1', e2'))
  
  (* Dla wyrażenia warunkowego, sprawdzamy czy możemy uprościć warunek *)
  | If (e1, e2, e3) ->
      let e1' = cp_env env e1 in
      (match e1' with
       | Bool true -> cp_env env e2  (* Jeśli warunek jest stałą true, zwracamy gałąź "then" *)
       | Bool false -> cp_env env e3 (* Jeśli warunek jest stałą false, zwracamy gałąź "else" *)
       | _ -> 
          (* W przeciwnym przypadku upraszczamy obie gałęzie *)
          let e2' = cp_env env e2 in
          let e3' = cp_env env e3 in
          If(e1', e2', e3'))
  
  (* Dla let-wyrażeń, rozważamy dwa przypadki *)
  | Let (x, e1, e2) ->
      let e1' = cp_env env e1 in
      (match e1' with
       (* Jeśli e1 upraszcza się do stałej, zastępujemy x przez tę stałą w e2 *)
       | Int _ | Bool _ -> 
          cp_env (EM.add x e1' env) e2
       (* W przeciwnym razie, upraszczamy e2 zakładając, że x = Var x *)
       | _ -> 
          Let(x, e1', cp_env (EM.add x (Var x) env) e2))

(* Główna funkcja propagacji stałych *)
let cp (e : expr) : expr =
  cp_env EM.empty e
let interp (s : string) : value =
  eval (parse s)
