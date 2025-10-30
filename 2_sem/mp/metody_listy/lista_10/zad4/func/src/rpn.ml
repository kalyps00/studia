(* Składnia RPN *)

type cmd =
  | PushInt of int
  | Binop   of Ast.bop
  | PushVar of string

type prog = cmd list

(* Kompilacja do RPN *)

let rec of_ast (expr : Ast.expr) : prog =
  match expr with
  | Ast.Int n -> [PushInt n]
  | Ast.Binop (op, e1, e2) -> of_ast e1 @ of_ast e2 @ [Binop op]
  | Ast.Var x -> [PushVar x]
  | _ -> failwith "not implemented"

(* Ewaluator dla RPN *)
let convert_to_rpn (expr : string) : prog =
  let ast = Interp.parse expr in  (* Parsowanie wyrażenia do AST *)
  of_ast ast

let eval_op (op : Ast.bop) (val1 : int) (val2 : int) : int =
  match op, val1, val2 with
  | Add,  v1, v2 -> v1 + v2
  | Sub,  v1, v2 -> v1 - v2
  | Mult, v1, v2 -> v1 * v2
  | Div,  v1, v2 -> v1 / v2
  | _, _, _ -> failwith ""

(* ewaluator nie jest elementem procesu kompilacji, ale
 * przydaje się do testowania i debugowania
 *)
 module StringMap = Map.Make(String)
 let create_env (bindings : (string * int) list) : int StringMap.t =
  List.fold_left (fun acc (k, v) -> StringMap.add k v acc) StringMap.empty bindings
let env = create_env [("x", 3); ("y", 5)]

(* eval [] (convert_to_rpn "2+2*x") env ;; *) (* test *)
let rec eval (s : int list) (p : prog ) (env : int StringMap.t) : int =
  match p, s with
  | [], [n] -> n
  | [], _   -> failwith "error!"
  | (PushInt n :: p'), _ -> eval (n :: s) p' env
  | (Binop op :: p'), (v2 :: v1 :: s') ->
      eval (eval_op op v1 v2 :: s') p' env
  | (PushVar x :: p'), s -> (
    match StringMap.find_opt x env with
    | Some value -> eval (value:: s) p' env
    | None -> failwith ("Variable " ^ x ^ " not found in environment")
  )
  | _ -> failwith "error!!"

(* Kompilacja RPN do podzbioru C *)

(* Runtime:
 * - Stos to tablica int-ów.
 * - Wskaźnik stosu pokazuje na pierwszy element (inaczej
 *   niż na wykładzie).
 *)

let with_runtime p =
  Printf.sprintf
  {|
#include <stdio.h>

int stack[10000];
int stack_ptr = -1;

int main()
{
%s
  printf("%%d\n", stack[0]);
  return 0;
}
  |}
  p

(* Przdałaby się jeszcze jedna warstwa abstrakcji,
 * żeby ograniczyć takie majtanie stringami, które
 * na dłuższą metę jest nie do utrzymania.
 *)

let emit_bop (op : Ast.bop) : string =
  Ast.(match op with
  | Add  -> "+"
  | Sub  -> "-"
  | Mult -> "*"
  | Div  -> "/"
  | _ -> failwith "not implemented")

let emit_line (s : string) : string =
  "  " ^ s ^ ";\n"

let emit_cmd (c : cmd) : string =
  match c with
  | PushInt n ->
      emit_line "stack_ptr++" ^
      emit_line ("stack[stack_ptr] = " ^ string_of_int n)
  | Binop op ->
      emit_line "stack_ptr--" ^
      emit_line ("stack[stack_ptr] = stack[stack_ptr] " ^ emit_bop op ^ " stack[stack_ptr+1]")
  | PushVar _ -> failwith "not implemented"

let emit (p : prog) : string =
  List.fold_left (fun res cmd -> res ^ emit_cmd cmd) "" p

let compile (s : string) : string =
  s
  |> Interp.parse
  |> of_ast
  |> emit
  |> with_runtime
