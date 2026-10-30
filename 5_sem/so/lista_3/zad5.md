### Przeznaczenie funkcji `Setjmp` i `Longjmp`

- `Setjmp`: Zapisuje aktualny kontekst wykonania (stan wybranych rejestrów i wskaźnika stosu) do bufora `env` i zwraca wartość 0.
- `Longjmp`: Odtwarza zapisany kontekst z bufora i wznawia działanie programu w taki sposób, jakby funkcja `Setjmp` właśnie zwróciła podaną wartość `val`. Umożliwia to wykonywanie skoków nielokalnych.

### Dlaczego `Jmpbuf` nie przechowuje wszystkich rejestrów procesora

Wynika to z konwencji wywołań architektury x86-64, która dzieli rejestry na caller-saved oraz callee-saved. Z tego powodu struktura `Jmpbuf` musi przechowywać wyłącznie wskaźniki stosu i instrukcji oraz rejestry callee-saved (`rbx`, `rbp`, `r12`-`r15`)

### Cel zapisywania wartości na stos przed wykonaniem instrukcji `ret` w `Longjmp`

Instrukcja `ret` pobiera docelowy adres skoku bezpośrednio ze szczytu stosu. Gdy `Longjmp` przywraca historyczny wskaźnik stosu (`%rsp`) pobrany z bufora, na szczycie tego stosu mogą znajdować się śmieci, ponieważ pamięć mogła zostać nadpisana w trakcie późniejszego działania programu. Ręczne umieszczenie oryginalnego adresu powrotu (`%r11`) na odtworzonym szczycie stosu (`(%rsp)`) tuż przed wywołaniem `ret` gwarantuje, że procesor poprawnie powróci do instrukcji bezpośrednio następującej po pierwotnym wywołaniu `Setjmp`.
