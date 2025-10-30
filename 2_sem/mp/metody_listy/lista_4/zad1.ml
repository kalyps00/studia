module type DICT = sig
    type ('a , 'b ) dict
    val empty : ('a , 'b ) dict
    val insert : 'a -> 'b -> ('a , 'b ) dict -> ('a , 'b ) dict
    val remove : 'a -> ('a , 'b ) dict -> ('a , 'b ) dict
    val find_opt : 'a -> ('a , 'b ) dict -> 'b option
    val find : 'a -> ('a , 'b ) dict -> 'b
    val to_list : ('a , 'b ) dict -> ('a * 'b ) list
end

module ListDict : DICT = struct
  type ('a, 'b) dict = ('a * 'b) list
  let empty = []

  let rec remove k d =
    match d with
    | [] -> []
    | (k', v) :: t->
        if k'=k then t else (k', v) :: remove k t

  let insert k v d = (k, v) :: remove k d

  let rec find_opt k d=
  match d with 
  |[] -> None 
  |(k', v) :: t -> if k'=k then Some v else find_opt k t

  let rec find k d=
  match find_opt k d with 
  |None -> failwith "brak elementu"
  |Some x -> x 
  
  let to_list d = d
end