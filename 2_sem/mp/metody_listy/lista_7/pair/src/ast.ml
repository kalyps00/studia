type bop =
  (* arithmetic *)
  | Add | Sub | Mult | Div
  (* logic *)
  | And | Or
  (* comparison *)
  | Eq | Leq

type ident = string

type expr = 
  | Int   of int
  | Binop of bop * expr * expr
  | Bool  of bool
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident
  | Unit
  | Pair  of expr * expr
  | Fst   of expr
  | Snd   of expr
  | Match of expr * ident * ident * expr
  | Is_Number of expr(* 2 *)
  | Is_Boolean of expr(* 2 *)
  | Is_Pair of expr(* 2 *)
  | Is_Unit of expr(* 2 *)
  | Fold of expr * ident * ident * expr * expr