(* Składnia NP *)

type cmd =
  | PushInt of int
  | Binop   of Ast.bop

type prog = cmd list

(* Kompilacja do NP *)

let rec of_ast (expr : Ast.expr) : prog =
  match expr with
  | Ast.Int n -> [PushInt n]
  | Ast.Binop (op, e1, e2) -> [Binop op] @ of_ast e1 @ of_ast e2
  | _ -> failwith "not implemented"


let string_of_cmd (c : cmd ) : string =
  match c with
  | PushInt n -> string_of_int n
  | Binop op -> 
    (match op with
    | Add -> "+"
    | Sub -> "-"
    | Mult -> "*"
    | Div -> "/"
    | _ -> failwith "unexpected binary operator"
    )
  
let show_ast s = Interp.parse s

let print_pn s = List.fold_left 
                  (fun (res : string) (c : cmd) : string -> res ^ string_of_cmd c)
                  ""
                  (of_ast (Interp.parse s))