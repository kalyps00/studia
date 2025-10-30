(*zadanie 1*)
let rec fib n = 
  if n = 0 then 0 
  else if n=1 then 1
  else (fib (n-1)) + (fib (n-2));;


let fib_iter n =
  let rec help n a b = 
    if n=0 then a 
    else help (n-1) b (a+b)
  in help n 0 1;;
(*zadanie 2*)
let matrix_mult (a, b, c, d) (e, f, g, h) =  
  (a*e + b*g, a*f+b*h, c*e + d*g, c*f+d*h);;

let matrix_id = (1, 0, 0, 1);;

let rec matrix_expt m k = 
  if k = 0 then matrix_id
  else matrix_mult m (matrix_expt m (k-1));;

let fib_matrix k = 
  let (_, _ , kfib, _) = matrix_expt (1,1,1,0) k in kfib;;

(*zadanie 3*)

let rec matrix_expt_fast m k = 
  if k = 0 then matrix_id 
  else if k mod 2 = 0 then
    let half = matrix_expt_fast m (k/2) in
    matrix_mult half half 
  else matrix_mult m (matrix_expt_fast m (k-1));;

  let fib_matrix k = 
    let (_ ,_, kfib, _ ) = matrix_expt_fast (1,1,1,0) k in kfib;;

(*zadanie 4*)
let rec mem x xs = 
  match xs with
  | [] -> false
  | h :: t -> (h=x) || mem x t;;
  (*matchuje xs (liste) z glowa listy i tailem  wtedy h moze byc tym x 
  i zwroci true lub mem x t czyli nowa liste bez pierwzgo*)

  (*zadanie 5*)
  let rec maximum xs =
    match xs with
    | [] -> neg_infinity
    | h::t ->
        let maxi = maximum  t in
        if(h>maxi) then h
        else maximum;;
  (*zadanie 6*)
  let suffixes xs =
    let rec help k = 
      match k with
      |[] -> [[]]
      |h::t -> (h::t) :: help t 
    in 
    help xs;;
      (*zadanie 7*)
  let rec is_sorted xs =
    match xs with 
    | [] | [_]-> true;
    |h1:: h2:: t -> if h1>h2 then false else is_sorted (h2::t);;
    
    (*zadanie 8*)
let rec select xs =
  match xs with 
  | []-> failwith "Pusta"
  | [x] -> (x , [])
  | x::xs' -> 
    let (m, rest) = select xs' in
    if x<=m then (x, xs') 
    else (m, x::rest);;

let rec select_sort xs = 
  match xs with 
  | []-> []
  | _ -> 
  let (min_elem, rest) = select xs in
  min_elem :: select_sort rest;;

