let list_of_string s = String . to_seq s |> List . of_seq
let parens_ok s = 
  let drugi = function 
  | '(' -> ')'
  | '[' -> ']'
  | '{' -> '}'
  | _ -> failwith "blad"; 
in
let rec check stack  = function
| []-> (stack = [])
| x :: xs -> 
  if x= '(' || x ='[' || x = '{' then check ( drugi x :: stack ) xs
  else if x = ')' || x= ']' || x= '}' then 
    match stack with 
    |[] -> false
    | top :: rest -> 
      if x =top then check rest xs 
      else false
  else false
in 
check [] ( list_of_string s)
  
