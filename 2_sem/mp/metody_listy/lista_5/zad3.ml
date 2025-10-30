let list_of_string s = String . to_seq s |> List . of_seq
let parens_ok s = 
  let rec check balance = function 
  |[] -> (balance = 0)
  |x :: xs -> 
    if x = '(' then check (balance+1) xs
    else if x = ')' then
      if balance >0 then check (balance-1) xs
      else false
    else false
  in
  let char_list = list_of_string s in
  check 0 char_list