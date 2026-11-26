Co robi ext2 przy tworzeniu dowiązania twardego:

- Nie tworzy nowego i-węzła ani nie kopiuje bloków danych.
- Dodaje nowy wpis w katalogu, który wiąże nową nazwę z numerem istniejącego i-węzła.
- Zwiększa o 1 licznik dowiązań (i_links_count) w tym i-węźle oraz aktualizuje czasy (ctime i-węzła, mtime i ctime katalogu).
- Obie nazwy są równoprawne i muszą leżeć w obrębie tego samego systemu plików.

Co robi ext2 przy tworzeniu dowiązania symbolicznego (symlink):

- Alokuje nowy, osobny i-węzeł (zapala bit w bitmapie i-węzłów), ustawia jego typ (i_mode) na dowiązanie symboliczne (S_IFLNK) i ustawia i_links_count = 1.
- Zapisuje ścieżkę docelową jako zawartość dowiązania (pole i_size to długość tej ścieżki).
- Dodaje nowy wpis w katalogu wskazujący na ten nowy i-węzeł.
- Nie modyfikuje i-węzła celu - plik docelowy nie musi nawet istnieć ani leżeć na tym samym systemie plików.

Gdzie jest przechowywana zawartość dowiązania symbolicznego:

- Krótkie ścieżki do 60 bajtów (fast symlink) - zapisywane są bezpośrednio wewnątrz i-węzła, w miejscu tablicy wskaźników na bloki danych. Nie alokuje się żadnego bloku danych (i_blocks = 0).
- Dłuższe ścieżki powyżej 60 bajtów (slow symlink) - alokowany jest normalny blok danych, a i_block przechowuje zwykły wskaznik.

Jak stworzyć pętlę za pomocą dowiązania symbolicznego:

- Bezpośrednio na siebie: ln -s a a
- Wzajemnie: ln -s b a oraz ln -s a b

Kiedy jądro wykrywa pętlę i zwraca błąd ELOOP:

- Jądro nie sprawdza cykli przy tworzeniu dowiązania (symlink), bo nie analizuje grafu katalogów.
- Wykrywanie zachodzi dopiero podczas rozwiązywania ścieżki (np. przy open, stat, chdir). Jądro po prostu zlicza, ile dowiązań symbolicznych rozwinęło po drodze.
- Gdy liczba rozwinięć przekroczy sztywny limit domyslnie 40, jądro przerywa operację i zwraca błąd ELOOP. Skutek uboczny: nawet poprawny, niezapętlony łańcuch ponad 40 symlinków też zwróci ELOOP.

Czemu pętli nie da się zrobić dowiązaniem twardym:

- System operacyjny zabrania tworzenia dowiązań twardych do katalogów (link na katalogu zwraca EPERM; wyjątkiem są wpisy . oraz .. zarządzane przez jądro).
- Dzięki temu hierarchia katalogów zawsze pozostaje drzewem (bez cykli), a każdy katalog ma dokładnie jednego rodzica (jednoznaczny wpis ..).
- Pozwala to zwalniać miejsce na dysku prostym zliczaniem referencji (i_links_count). Gdyby cykle katalogów były możliwe, odcięty od korzenia cykl miałby i_links_count > 0 i nigdy by się nie usunął
