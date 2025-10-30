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


(* Ewaluator *)

let print_list (p : prog) : unit =
  print_endline (String.concat " " (List.map string_of_cmd p))

(* NOWE: *)
let eval_pn (s : string) =
  let p = of_ast (Interp.parse s) in
  
  (* Pomocnicza funkcja do wykonywania operacji *)
  let apply_op op a b =
    match op with
    | Ast.Add -> a + b
    | Ast.Sub -> a - b
    | Ast.Mult -> a * b
    | Ast.Div -> if b = 0 then failwith "Dzielenie przez zero" else a / b
    | _ -> failwith "Nieobsługiwany operator"
  in
  
  (* Funkcja, która sprawdza, czy można wykonać operację *)
  let rec process_stack stack =
    match stack with
    | PushInt b :: PushInt a :: Binop op :: tail ->
        process_stack (PushInt (apply_op op a b) :: tail)
    | _ -> stack
  in
  
  let rec eval_aux prog stack =
    match prog with
    | [] -> 
        (* Kiedy skończą się instrukcje, spróbuj wykonać wszystkie oczekujące operacje *)
        let final_stack = process_stack stack in
        (match final_stack with
        | [PushInt v] -> v
        | _ -> failwith "Nieprawidłowy stan stosu na końcu ewaluacji")
    
    | cmd :: rest ->
        (* Przetwórz aktualną instrukcję *)
        let new_stack = cmd :: stack in
        (* Próbuj wykonać operacje, jeśli to możliwe *)
        let processed_stack = process_stack new_stack in
        eval_aux rest processed_stack
  in
  
  eval_aux p []

(* ---- *)