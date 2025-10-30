open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

module M = Map.Make(String)

type env = value M.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env
  
type cell_status =
  | Unevaluated
  | Evaluating
  | Evaluated of value

exception Cycle_detected

let rec show_value v =
  match v with
  | VInt n -> string_of_int n
  | VBool v -> string_of_bool v
  | VUnit -> "()"
  | VPair (v1,v2) -> "(" ^ show_value v1 ^ ", " ^ show_value v2 ^ ")"
  | VClosure _ | VRecClosure _ -> "<fun>"

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Lt,   VInt  v1, VInt  v2 -> VBool (v1 < v2)
  | Gt,   VInt  v1, VInt  v2 -> VBool (v1 > v2)
  | Geq,  VInt  v1, VInt  v2 -> VBool (v1 >= v2)
  | Neq,  _,        _        -> VBool (val1 <> val2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

let rec eval_env_spreadsheet
    (spreadsheet_state : cell_status array array)
    (eval_cell_ref : int -> int -> value)
    (env : env)
    (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1) (eval_env_spreadsheet spreadsheet_state eval_cell_ref env e2)
  | If (b, t, el) ->
      (match eval_env_spreadsheet spreadsheet_state eval_cell_ref env b with
        | VBool true -> eval_env_spreadsheet spreadsheet_state eval_cell_ref env t
        | VBool false -> eval_env_spreadsheet spreadsheet_state eval_cell_ref env el
        | _ -> failwith "type error")
  | Var x ->
     (match M.find_opt x env with
       | Some v -> v
       | None -> failwith ("unknown var: " ^ x))
  | Let (x, e1, e2) ->
      let v1 = eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1 in
      eval_env_spreadsheet spreadsheet_state eval_cell_ref (M.add x v1 env) e2
  | Pair (e1, e2) -> VPair (eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1, eval_env_spreadsheet spreadsheet_state eval_cell_ref env e2)
  | Unit -> VUnit
  | Fst e1 ->
      (match eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1 with
        | VPair (v1, _) -> v1
        | _ -> failwith "Type error: Fst applied to non-pair")
  | Snd e1 ->
      (match eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1 with
        | VPair (_, v2) -> v2
        | _ -> failwith "Type error: Snd applied to non-pair")
  | IsPair e1 ->
      (match eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1 with
        | VPair _ -> VBool true
        | _ -> VBool false)
  | Fun (x, body) -> VClosure (x, body, env)
  | Funrec (f, x, body) -> VRecClosure (f, x, body, env)
  | App (e1, e2) ->
      let v1 = eval_env_spreadsheet spreadsheet_state eval_cell_ref env e1 in
      let v2 = eval_env_spreadsheet spreadsheet_state eval_cell_ref env e2 in
      (match v1 with
        | VClosure (x_fun, body_c, clo_env) ->
            eval_env_spreadsheet spreadsheet_state eval_cell_ref (M.add x_fun v2 clo_env) body_c
        | VRecClosure (f_rec, x_fun, body_r, clo_env) as closure_val ->
            eval_env_spreadsheet spreadsheet_state eval_cell_ref (clo_env |> M.add x_fun v2 |> M.add f_rec closure_val) body_r
        | _ -> failwith "not a function in App")
  | Cell (r_cell, c_cell) ->
      let num_rows_in_sheet = Array.length spreadsheet_state in
      let num_cols_in_sheet = if num_rows_in_sheet > 0 then Array.length spreadsheet_state.(0) else 0 in
      if r_cell < 0 || r_cell >= num_rows_in_sheet || c_cell < 0 || c_cell >= num_cols_in_sheet then
        failwith ("Cell (" ^ string_of_int r_cell ^ ", " ^ string_of_int c_cell ^ ") is out of bounds")
      else
        eval_cell_ref r_cell c_cell
  | Match (_e1, _x, _y, _e2) ->
    failwith "Not implemented"

let eval_spreadsheet (s : expr list list) : value list list option =
  if s = [] then Some [] else
  let num_rows = List.length s in
  let first_row = List.hd s in
  if first_row = [] then Some (List.map (fun _ -> []) s) else

  let num_cols = List.length first_row in

  let spreadsheet_state : cell_status array array =
    Array.init num_rows (fun r ->
      let row_exprs = List.nth s r in
      if List.length row_exprs <> num_cols then 
        failwith "Spreadsheet rows have inconsistent lengths";
      Array.make num_cols Unevaluated
    )
  in

  let rec eval_cell (r_idx : int) (c_idx : int) : value =
    match spreadsheet_state.(r_idx).(c_idx) with
    | Evaluated v -> v
    | Evaluating -> raise Cycle_detected
    | Unevaluated ->
        spreadsheet_state.(r_idx).(c_idx) <- Evaluating;
        let expr_in_cell = List.nth (List.nth s r_idx) c_idx in
        try
          let cell_value = eval_env_spreadsheet spreadsheet_state eval_cell M.empty expr_in_cell in
          spreadsheet_state.(r_idx).(c_idx) <- Evaluated cell_value;
          cell_value
        with
        | Cycle_detected ->
            spreadsheet_state.(r_idx).(c_idx) <- Evaluating;
            raise Cycle_detected
        | ex -> raise ex
  in

  try
    let result_values =
      List.mapi (fun r row_exprs ->
        List.mapi (fun c _expr ->
          eval_cell r c
        ) row_exprs
      ) s
    in
    Some result_values
  with
  | Cycle_detected -> None

let parse_and_eval_spreadsheet (s : string list list) : string list list option =
  let es = List.map (List.map parse) s in
  let vs = eval_spreadsheet es in
  Option.map (List.map (List.map show_value)) vs
