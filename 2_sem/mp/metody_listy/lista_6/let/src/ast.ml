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
  (* zad 2 *)
  (* | For of ident * expr * expr * expr
  | Integral of expr* expr * ident * expr *)
  | Unit  (* zad 3 *)
  | Pair of expr * expr (* zad 4 *)
  | Fst of expr (* zad 4 *)
  | Snd of expr (* zad 4 *)
  | Sum of ident * expr *expr * expr (* zad 6 *)