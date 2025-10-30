
console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] );

console.log("![]+[] =  " + ![]+[]) // ![] -> negacja truth -> false, false + [] -> "false" + "" -> false
console.log("+[] = " + Number(+[])) // +[] pusty string, jako number daje 0 wiec false[0] = f



console.log("+!+[] =  "+ +!+[]) // + konwertuje na liczbe []-> 0 !neguje wartosc wiec mamy konwersje na liczbe(!+[]) a [] przekonwertowane daje 0 wiec !0 = 1


console.log("[![]] = " + [![]]) // tablica zawierajaca element ![] czyli negacje pustej tablicy -> false
console.log("![] = " + ![]) //negacja pustej tablicy -> false
console.log("[][[]] = " + [][[]]) // [] -> toString "" teraz chcemy pusty string od indeksu pusta tablica a nie mamy czegos takiego wiec mamy undefined
console.log("[![]]+[][[]] = " + [![]]+[][[]]) // falseundefined -> polaczenie false i undefined


console.log("[+[]] = " + [+[]])// [0]
console.log("+!+[]+[+[]] = " + +!+[]+[+[]])// +!+[] to daje 1, wiec mamy 1 + [0] js konwertuje na stringi wiec "1" + "0" wiec "10"

//([![]]+[][[]])[+!+[]+[+[]]] calosc to jest falseundefined[10] -> i to mamy juz fai

console.log("(![]+[])") // to wiemy ze daje false
console.log("[!+[]+!+[]] = " + [!+[]+!+[]])
// !+[] negacja 0 -> 1 + negacja 0 -> 1+1 -> 2 wiec false[2] = l
// koniec koncow fail
