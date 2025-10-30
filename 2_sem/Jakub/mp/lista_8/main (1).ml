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
  
  let is_constant = function
  | Int _ | Bool _ -> true
  | _ -> false
 
 
 let rec cp_env env = function
     |Int i -> Int i
     |Bool b -> Bool b
     |Var x ->
       (
         try
           let e = List.assoc x env in
           if is_constant e then e else Var x
         with Not_found -> Var x
       )
     | Binop(op,e1,e2) ->
       let e1' = cp_env env e1 in
       let e2' = cp_env env e2 in
       (match e1',e2' with
         |Int a,Int b ->
           (match op with
             | Add -> Int (a + b)
             | Sub -> Int (a - b)
             | Mult -> Int (a * b)
             | Div -> Int (a / b)
             | Eq -> Bool (a = b)
             | Leq -> Bool (a <= b)
             | _ -> Binop (op, e1', e2'))
         | Bool a, Bool b ->
             (match op with
             | And -> Bool (a && b)
             | Or -> Bool (a || b)
             | Eq -> Bool (a = b)
             | _ -> Binop (op, e1', e2'))
         | _ -> Binop (op, e1', e2')
        )
     |If (b,t,e) ->
       let b' = cp_env env b in
       (match b' with
       |Bool true -> cp_env env t (* Jesli b to stała i true to upraszaczamy t*)
       |Bool false -> cp_env env e (* Jesli b to stała i false to upraszaczamy e*)
       |_ -> (* Jesli b nie jest stałą to robimy nowego ifa z uproszczonymi wszystkimi elementami*)
         let t' = cp_env env t in
         let e' = cp_env env e in
         If (b',t',e')
       )
     |Let (x,e1,e2) ->
       let e1' = cp_env env e1 in
       let new_env = 
         if is_constant e1' then (x,e1') :: env
         else (x,Var x) :: env
       in
       let e2' = cp_env new_env e2 in
        if is_constant e1' then
          e2'
        else
          Let (x,e1',e2')
    
       
  let cp e = cp_env [] e
let interp (s : string) : value =
  eval (parse s)
