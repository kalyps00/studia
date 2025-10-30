module type KDICT = sig
  type key
  type 'a dict
  val empty : 'a dict
  val insert : key -> 'a -> 'a dict -> 'a dict
  val remove : key -> 'a dict -> 'a dict
  val find_opt : key -> 'a dict -> 'a option
  val find :  key -> 'a dict -> 'a 
  val to_list : 'a dict -> (key * 'a) list
end;;

module MakeMapDict (Order : Map.OrderedType) : (KDICT with type key = Order.t) = struct
  module M = Map.Make(Order)
  type key = Order.t
  type 'a dict = 'a M.t
  let empty = M.empty
  let insert = M.add
  let remove = M.remove
  let find_opt = M.find_opt
  let find =  M.find
  let to_list = M.bindings
end;;

module CharOrder : Map.OrderedType = struct
  type t = char
  let compare = Char.compare 
  end;;
module CharMapDict = MakeMapDict(CharOrder);;