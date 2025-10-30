let is_bst tree =
  let rec check t min_val max_val =
    match t with
    | Leaf -> true
    | Node (left, v, right) ->
        (* Sprawdź czy wartość node'a mieści się w dopuszczalnym zakresie *)
        (match min_val with
         | None -> true
         | Some min -> v > min) 
        && 
        (match max_val with
         | None -> true
         | Some max -> v < max)
        (* Sprawdź rekurencyjnie poddrzewa *)
        && check left min_val (Some v)
        && check right (Some v) max_val
  in
  check tree None None

(* Funkcja mierząca wysokość drzewa (najdłuższą ścieżkę) *)
let height tree =
  let rec aux t =
    match t with
    | Leaf -> 0
    | Node(l, _, r) -> 1 + max (aux l) (aux r)
  in aux tree

(* Test sprawdzający czy drzewo jest α-wysokościowo zbalansowane *)
let test_tree_balance sgt =
  let tree_height = height sgt.tree in
  let alpha_h = alpha_height sgt.size in
  if tree_height > alpha_h + 1 then
    failwith (Printf.sprintf "Drzewo nie jest α-wysokościowo zbalansowane: wysokość=%d, α-wysokość=%d" 
              tree_height alpha_h)
  else
    Printf.printf "Drzewo jest poprawnie zbalansowane: wysokość=%d, α-wysokość=%d\n" 
                 tree_height alpha_h

let test_big_insert () =
  let rec insert_range sgt n acc =
    if n = 0 then (sgt, acc) else
      let value = Random.int 1_000_000 in
      if find value sgt then insert_range sgt n acc
      else
        let new_sgt = insert value sgt in
        insert_range new_sgt (n - 1) (value :: acc)
  in
  let start_time = Sys.time () in
  let final_sgt, inserted = insert_range empty 100_000 [] in
  let end_time = Sys.time () in
  Printf.printf "Wstawiono %d elementów w %.3f sekund.\n" (List.length inserted) (end_time -. start_time);
  if not (is_bst final_sgt.tree) then
    failwith "Końcowe drzewo po insert nie jest BST"
  else
    Printf.printf "Drzewo po insert jest poprawne BST.\n"

let test_big_remove () =
  let rec build_tree_from_list lst acc =
    match lst with
    | [] -> acc
    | x :: xs -> build_tree_from_list xs (insert x acc)
  in
  let values = List.init 100_000 (fun i -> i) in
  let sgt = build_tree_from_list values empty in
  if not (is_bst sgt.tree) then
    failwith "Początkowe drzewo nie jest BST"
  else
    let start_time = Sys.time () in
    let final_sgt =
      List.fold_left (fun acc x ->
        if x mod 2 = 0 then remove x acc else acc
      ) sgt values
    in
    let end_time = Sys.time () in
    Printf.printf "Usunięto połowę elementów w %.3f sekund.\n" (end_time -. start_time);
    if not (is_bst final_sgt.tree) then
      failwith "Końcowe drzewo po remove nie jest BST"
    else
      Printf.printf "Drzewo po remove jest poprawne BST.\n"

let test_mixed_operations () =
  let rec aux sgt i =
    if i > 100_000 then sgt
    else
      let sgt' = insert i sgt in
      let sgt'' = if i mod 3 = 0 then remove (i / 3) sgt' else sgt' in
      aux sgt'' (i + 1)
  in
  let start_time = Sys.time () in
  let final_sgt = aux empty 1 in
  let end_time = Sys.time () in
  Printf.printf "Wykonano 100k mieszanego insert/remove w %.3f sekund.\n" (end_time -. start_time);
  if not (is_bst final_sgt.tree) then
    failwith "Końcowe drzewo po mieszanych operacjach nie jest BST"
  else
    Printf.printf "Drzewo po mieszanych operacjach jest poprawne BST.\n"

let test_sequential_insert () =
  let start_time = Sys.time () in
  let final_sgt = 
    List.fold_left (fun acc i -> insert i acc) empty (List.init 100_000 (fun i -> i))
  in
  let end_time = Sys.time () in
  
  Printf.printf "Wstawienie 100k elementów w kolejności rosnącej: %.3f sekund\n" (end_time -. start_time);
  
  if not (is_bst final_sgt.tree) then
    failwith "Końcowe drzewo nie jest BST"
  else
    test_tree_balance final_sgt;
  
  (* Zmierzmy również czas przeszukiwania *)
  let search_start = Sys.time () in
  for i = 0 to 99_999 do
    ignore (find i final_sgt)
  done;
  let search_end = Sys.time () in
  
  Printf.printf "Przeszukiwanie 100k elementów: %.3f sekund\n" (search_end -. search_start)

(* Zmodyfikowana funkcja insert z licznikiem przebudowań *)
let insert_with_counter x sgt =
  let rebuild_count = ref 0 in
  
  let rec go_up_with_scapegoat t path tree_size =
    match path with
    | [] -> t
    | Left(v, r) :: rest_path -> 
        let sub_tree = Node(t, v, r) in
        let size_r = size r in
        if not (is_balanced sub_tree tree_size size_r) then
          begin
            incr rebuild_count;
            let new_tree = rebuild_balanced sub_tree in
            go_up new_tree rest_path
          end
        else
          go_up_with_scapegoat sub_tree rest_path (size_r + tree_size + 1)
    | Right(l, v) :: rest_path -> 
        let sub_tree = Node(l, v, t) in
        let size_l = size l in
        if not (is_balanced sub_tree size_l tree_size) then
          begin
            incr rebuild_count;
            let new_tree = rebuild_balanced sub_tree in
            go_up new_tree rest_path
          end
        else
          go_up_with_scapegoat sub_tree rest_path (size_l + tree_size + 1)
  in
  
  (* Regularna implementacja insert *)
  let rec go_down t path depth = 
    match t with 
    | Leaf -> Node(Leaf, x, Leaf), path, depth
    | Node (l, v, r) -> 
        if x < v then go_down l (Left(v,r) :: path) (depth+1)
        else if x > v then go_down r (Right(l,v) :: path) (depth+1)
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
    max_size = max sgt.max_size new_size }, !rebuild_count

(* Funkcja sprawdzająca czy drzewo jest BST *)

let test_insertion_patterns () =
  (* Wzorzec 1: Losowe wartości *)
  let start_random = Sys.time () in
  let sgt_random = ref empty in
  let rebuilds_random = ref 0 in
  for i = 1 to 10_000 do
    let value = Random.int 1_000_000 in
    if not (find value !sgt_random) then
      let new_sgt, rebuilds = insert_with_counter value !sgt_random in
      sgt_random := new_sgt;
      rebuilds_random := !rebuilds_random + rebuilds
  done;
  let end_random = Sys.time () in
  
  (* Wzorzec 2: Rosnące wartości *)
  let start_asc = Sys.time () in
  let sgt_asc = ref empty in
  let rebuilds_asc = ref 0 in
  for i = 1 to 10_000 do
    let new_sgt, rebuilds = insert_with_counter i !sgt_asc in
    sgt_asc := new_sgt;
    rebuilds_asc := !rebuilds_asc + rebuilds
  done;
  let end_asc = Sys.time () in
  
  (* Wzorzec 3: Malejące wartości *)
  let start_desc = Sys.time () in
  let sgt_desc = ref empty in
  let rebuilds_desc = ref 0 in
  for i = 10_000 downto 1 do
    let new_sgt, rebuilds = insert_with_counter i !sgt_desc in
    sgt_desc := new_sgt;
    rebuilds_desc := !rebuilds_desc + rebuilds
  done;
  let end_desc = Sys.time () in
  
  Printf.printf "\n--- Porównanie wzorców wstawiania (10k elementów) ---\n";
  Printf.printf "Losowe wartości: %.3fs, %d przebudowań, wysokość=%d\n" 
    (end_random -. start_random) !rebuilds_random (height (!sgt_random).tree);
  Printf.printf "Rosnące wartości: %.3fs, %d przebudowań, wysokość=%d\n" 
    (end_asc -. start_asc) !rebuilds_asc (height (!sgt_asc).tree);
  Printf.printf "Malejące wartości: %.3fs, %d przebudowań, wysokość=%d\n" 
    (end_desc -. start_desc) !rebuilds_desc (height (!sgt_desc).tree)

let test_operation_times () =
  let n = 10_000 in
  let values = Array.init n (fun _ -> Random.int 1_000_000) in
  
  (* Przygotowanie drzewa *)
  let sgt = ref empty in
  for i = 0 to n/2 - 1 do
    if not (find values.(i) !sgt) then 
      sgt := insert values.(i) !sgt
  done;
  
  (* Pomiar czasu poszczególnych operacji *)
  let insert_times = Array.make (n/2) 0. in
  let find_times = Array.make n 0. in
  let remove_times = Array.make (n/2) 0. in
  
  (* Pomiar czasu insert *)
  for i = n/2 to n - 1 do
    let start_time = Sys.time () in
    if not (find values.(i) !sgt) then 
      sgt := insert values.(i) !sgt;
    let end_time = Sys.time () in
    insert_times.(i - n/2) <- end_time -. start_time
  done;
  
  (* Pomiar czasu find *)
  for i = 0 to n - 1 do
    let start_time = Sys.time () in
    ignore (find values.(i) !sgt);
    let end_time = Sys.time () in
    find_times.(i) <- end_time -. start_time
  done;
  
  (* Pomiar czasu remove *)
  for i = 0 to n/2 - 1 do
    let start_time = Sys.time () in
    if find values.(i) !sgt then
      sgt := remove values.(i) !sgt;
    let end_time = Sys.time () in
    remove_times.(i) <- end_time -. start_time
  done;
  
  (* Obliczenie statystyk *)
  let avg_insert = Array.fold_left (+.) 0. insert_times /. float_of_int (n/2) in
  let avg_find = Array.fold_left (+.) 0. find_times /. float_of_int n in
  let avg_remove = Array.fold_left (+.) 0. remove_times /. float_of_int (n/2) in
  
  Printf.printf "\n--- Średnie czasy operacji (ms) ---\n";
  Printf.printf "Insert: %.6f ms\n" (avg_insert *. 1000.);
  Printf.printf "Find: %.6f ms\n" (avg_find *. 1000.);
  Printf.printf "Remove: %.6f ms\n" (avg_remove *. 1000.)

let () =
  Random.self_init ();
  
  (* Istniejące testy *)
  test_big_insert (); 
  test_big_remove ();
  test_mixed_operations ();
  
  (* Nowe testy *)
  test_sequential_insert ();
  test_insertion_patterns ();
  test_operation_times ()