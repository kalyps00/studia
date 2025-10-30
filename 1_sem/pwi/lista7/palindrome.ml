(* Funkcja sprawdzająca, czy dany ciąg znaków jest palindromem *)
let is_palindrome s =
  let len = String.length s in
  let rec aux i =
    if i >= len / 2 then true
    else if String.get s i <> String.get s (len - i - 1) then false
    else aux (i + 1)
  in
  aux 0

(* Funkcja znajdująca najdłuższy palindrom w tekście *)
let find_longest_palindrome filename =
  let ic = open_in filename in
  let rec process_lines longest_palindrome =
    try
      let line = input_line ic in
      let words = String.split_on_char ' ' line in
      let current_longest =
        List.fold_left
          (fun acc word ->
             let clean_word = String.lowercase_ascii (String.trim word) in
             if is_palindrome clean_word && String.length clean_word > String.length acc
             then clean_word
             else acc)
          longest_palindrome words
      in
      process_lines current_longest
    with End_of_file ->
      close_in ic;
      longest_palindrome
  in
  process_lines ""

let () =
  let filename = "1984.txt" in
  let longest_palindrome = find_longest_palindrome filename in
  Printf.printf "Najdłuższy palindrom w pliku: %s\n" longest_palindrome
