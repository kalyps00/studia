let alpha_num = 3
let alpha_denom = 4

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }

let alpha_height (n : int) : int = 
  if n <= 0 then 0
  else int_of_float (log (float_of_int n) /. log (float_of_int alpha_denom /. float_of_int alpha_num))

let rebuild_balanced (t : 'a tree) : 'a tree =
  let rec flatten t (xs, len) = 
    match t with
    | Leaf -> (xs, len)
    | Node (l, v, r) -> 
        let (r_xs, r_len) = flatten r (xs, len) in
        flatten l (v :: r_xs, r_len + 1)  
  in 
  let (tree_list, len) = flatten t ([], 0) 
  in 
  let rec build_bst lst len =
    if len = 0 then (Leaf, lst)
    else
      let left_len = len / 2 in
      let right_len = len - left_len - 1 in
      let (left_tree, rest1) = build_bst lst left_len in
      match rest1 with
      | [] -> failwith "Unexpected empty list"
      | x :: rest2 ->
          let (right_tree, rest3) = build_bst rest2 right_len in
          (Node (left_tree, x, right_tree), rest3)
  in 
  fst (build_bst tree_list len)

let empty : 'a sgtree = { tree = Leaf; size = 0; max_size = 0 }

let find (x : 'a) (sgt : 'a sgtree) : bool =
  let rec aux = function
    | Leaf -> false
    | Node (l, v, r) -> 
        if x < v then aux l
        else if x > v then aux r
        else true
  in 
  aux sgt.tree 

let rec size t = 
  match t with
  | Leaf -> 0
  | Node (l, _, r) -> 1 + size l + size r

let is_balanced t left_size right_size = 
  match t with 
  | Leaf -> true
  | Node (_, _, _) -> 
      let subtree_size = left_size + right_size + 1 in
      left_size * alpha_denom <= subtree_size * alpha_num &&
      right_size * alpha_denom <= subtree_size * alpha_num

(* zipper *)
type 'a direction =     
  | Left of 'a * 'a tree  
  | Right of 'a tree * 'a 

let rec go_up t path = 
  match path with 
  | [] -> t
  | Left (v, r) :: rest_path -> go_up (Node (t, v, r)) rest_path
  | Right (l, v) :: rest_path -> go_up (Node (l, v, t)) rest_path

let rec go_up_with_scapegoat t path tree_size =
  match path with
  | [] -> t
  | Left (v, r) :: rest_path -> 
      let sub_tree = Node (t, v, r) in
      let size_r = size r in
      if not (is_balanced sub_tree tree_size size_r) then
        let new_tree = rebuild_balanced sub_tree in
        go_up new_tree rest_path
      else
        go_up_with_scapegoat sub_tree rest_path (size_r + tree_size + 1)
  | Right (l, v) :: rest_path -> 
      let sub_tree = Node (l, v, t) in
      let size_l = size l in
      if not (is_balanced sub_tree size_l tree_size) then
        let new_tree = rebuild_balanced sub_tree in
        go_up new_tree rest_path
      else
        go_up_with_scapegoat sub_tree rest_path (size_l + tree_size + 1)
(* end of zipper *)

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let rec go_down t path depth = 
    match t with 
    | Leaf -> Node (Leaf, x, Leaf), path, depth
    | Node (l, v, r) -> 
        if x < v then go_down l (Left (v, r) :: path) (depth + 1)
        else if x > v then go_down r (Right (l, v) :: path) (depth + 1)
        else failwith "Element already exists"
  in 
  let (new_tree, path, depth) = go_down sgt.tree [] 0 in
  let new_size = sgt.size + 1 in
  let a_height = alpha_height new_size in
  let new_tree =
    if depth > a_height then
      go_up_with_scapegoat new_tree path 0
    else
      go_up new_tree path
  in
  { tree = new_tree;
    size = new_size;
    max_size = max sgt.max_size new_size }

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let rec delete x t = 
    match t with
    | Leaf -> failwith "Element not found"
    | Node (l, v, r) -> 
        if x < v then Node (delete x l, v, r)
        else if x > v then Node (l, v, delete x r) 
        else match (l, r) with
        | (Leaf, _) -> r 
        | (_, Leaf) -> l
        | (_, _) -> 
            let rec min_node = function
              | Node (Leaf, v, _) -> v
              | Node (l, _, _) -> min_node l
              | Leaf -> failwith "Unexpected empty tree"
            in 
            let min_r = min_node r in
            Node (l, min_r, delete min_r r)
  in
  let deleted_tree = delete x sgt.tree in
  let new_size = sgt.size - 1 in
  if new_size * alpha_denom < sgt.max_size * alpha_num then
    { tree = rebuild_balanced deleted_tree; 
      size = new_size; 
      max_size = new_size } 
  else
    { tree = deleted_tree;
      size = new_size;
      max_size = sgt.max_size }