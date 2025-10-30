(*1*)
let product lst = List.fold_left ( * ) 1 lst;;
(*2*)
let compose f g = fun x -> f(g x);;
(*3*)
let build_list n f = List.init n f;;
(*or*)
let build_list n f = 
  let rec help i = 
    if(i>=n) then [] else (f i) :: help (i+1)
  in help 0;;

let negatives n = build_list n (fun x -> -1 * (x+1));;
let reciprocal n  = build_list n (fun x -> 1.0 /. float_of_int(x+1));;
let evens n = build_list n (fun x -> 2*x);;

let idetityM n = 
  build_list n (fun x -> build_list n (fun y -> if x= y then 1 else 0));;
(*4*)
(*funckja z a' -> bool*)
let empty_set = fun _ -> false;;
let singleton a = fun x -> x=a;;
let in_set a s = s a;;
let union s t = fun x -> s x || t x;;
let intersect s t = fun x -> s x && t x;; 
(*5*)
type 'a tree = 
| Leaf 
| Node of 'a tree * 'a * 'a tree;;
let rec insert_bst x t = 
  match t with 
  |Leaf -> Node (Leaf , x , Leaf)
  |Node(l, v, r) -> if x=v then t 
    else if x<v then Node (insert_bst x l, v, r)
    else Node (l , v ,insert_bst x r);;

    5
    / \
   2   8
      / \
     6   9
      \
       7
(*6*)
let test_tree =
  Node (
    Node (Leaf, 2, Leaf),   (* lewe poddrzewo: liść z wartością 2 *)
    5,                      (* wartość w korzeniu: 5 *)
    Node (
      Node (Leaf, 6, Leaf), (* lewe poddrzewo z wartością 6 *)
      8,                    (* wartość węzła: 8 *)
      Node (Leaf, 9, Leaf)  (* prawe poddrzewo z wartością 9 *)
    )
  );;
   5
  / \
 2   8
    / \
   6   9
let rec fold_tree f a t = 
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r);;

let tree_product t = fold_tree (fun x y z -> x*y*z) 1 t;;
let tree_flip t = fold_tree (fun left v right -> Node(right, v , left)) Leaf t;;
let tree_height t = fold_tree  (fun l _ r -> 1 + (max l r)) 0 t ;;

let tree_span t = 
  let rec min_node = function
  | Node (Leaf, v , _) -> v
  | Node (l , _ , _) -> min_node l
in 
  let rec max_node = function
  | Node (_, v , Leaf) -> v
  | Node (_ , _ , r) -> max_node r
in 
match t with 
 | Leaf -> failwith "puste"
 | _ -> (min_node t , max_node t);;

let flatten t  = fold_tree (fun l v r -> l @ [v] @r ) [] t;;
(*7*)
let rec flat_append t xs= 
match t with
|Leaf -> xs
| Node (l, v, r)-> flat_append l (v :: flat_append r xs);;

let flatten t = flat_append t [];;
(*8*)

let rec insert_bst_dup x t = 
  match t with 
  |Leaf -> Node (Leaf , x , Leaf)
  |Node(l, v, r) -> 
    if x<v then Node (insert_bst_dup x l, v, r)
    else Node (l , v ,insert_bst_dup x r);; 

let tree_sort xs = 
  let bst = List.fold_left (fun t x -> insert_bst_dup x t) Leaf xs
in
flatten bst;;
(*9*)
  let rec delete x t = 
    match t with
    | Leaf -> Leaf
    | Node (l, v ,r)-> 
    if x<v then delete x l (*lewo*)
    else if x>v then delete x r (*prawo*)
    else match (l, r) with (*t
    utaj*)
    | (Leaf, _) ->  r (*proste drzewo po prostu zwrcamy nastepny el nizej to samo*)
    | (_, Leaf) -> l
    | (_, _) -> (*ma lewe i prawe*)
      let rec min_node = function
      | Node (Leaf, v , _) -> v
      | Node (l , _ , _) -> min_node l
      | Leaf -> failwith "kompilator krzyczy a tak nie moze byc "
      in 
      let min_r = min_node r in
      Node (l, min_r, delete min_r r);;

