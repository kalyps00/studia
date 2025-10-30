module type KDICT = sig
  type key
  type 'a dict
  val empty : 'a dict
  val insert : key -> 'a -> 'a dict -> 'a dict
  val remove : key -> 'a dict -> 'a dict
  val find_opt : key -> 'a dict -> 'a option
  val find :  key -> 'a dict -> 'a 
  val to_list : 'a dict -> (key * 'a) list
end

module MakeListDict (Order : Map.OrderedType) : (KDICT with type key = Order.t)= struct
  type key = Order.t
  type 'a dict = (key * 'a) list
  let empty = []
  let rec remove k xs = 
  match xs with
  |[] -> []
  |(k' , v) :: t -> if (Order.compare k k')=0 then t else (k', v) :: remove k t

  let insert k v d = (k, v) :: remove k d

  let rec find_opt k d =
  match d with 
  |[] -> None 
  |(k', v) :: t -> if (Order.compare k k')=0 then Some v else find_opt k t

  let rec find k d=
  match find_opt k d with 
  |None -> failwith "brak elementu"
  |Some x -> x 
  
  let to_list d = d
  end;;
  
  module CharOrder : (Map.OrderedType) = struct
  type t = char
  let compare = Char.compare
  end;;

  module CharListDict = MakeListDict(CharOrder);;