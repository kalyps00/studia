let i = ref 1 in
let x = ref 1 in
while !i <= 5 do
  x := !x * !i;
  i := !i + 1
;
!x