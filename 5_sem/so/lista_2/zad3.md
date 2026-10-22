### Zadanie 3

#### 1. Krytyka `fork()`

- Brak kompozycyjności: `fork()` wymaga, aby każdy element systemu (wątki, biblioteki, akceleratory GPU) wspierał klonowanie. Jeśli jeden komponent tego nie obsługuje dochodzi do błędów i undefined behavior
- Niezgodność z wątkami: Kopiowany jest tylko wątek wywołujący `fork()`. Jeśli inne wątki trzymały w tym czasie muteksy, w potomku pozostaną one zablokowane na zawsze
- Zagrożenie dla bezpieczeństwa: `fork()` kopiuje całą pamięć rodzica – w tym wrażliwe sekrety, klucze kryptograficzne i zrandomizowany układ pamięci (omijanie zabezpieczeń ASLR)
- Niska wydajność: Duplikowanie tablic stron przy mechanizmie Copy-On-Write (COW) dla dużych procesów jest bardzo wolne i trwa kilkadziesiąt milisekund (w porównaniu do ~0,5 ms dla `posix_spawn`)

#### 2. Obrona `fork()`

- Całkowity brak parametrów wejściowych w przeciwieństwie do skomplikowanego `CreateProcess` w systemie Windows
- Rozdzielenie tworzenia procesu od ładowania nowego programu daje powłoce okno czasowe na przekierowanie strumieni I/O (potoki, pliki) przed uruchomieniem docelowego kodu

#### 3. Jak `posix_spawn()` rozwiązuje te problemy?

- Tworzy nowy proces i ładuje nowy program w jednej, atomowej operacji.
- Całkowicie unika zbędnego i kosztownego kopiowania tablic stron oraz rozwiązuje problem zakleszczeń wątków.
- Zamiast ręcznego manipulowania deskryptorami w kodzie, przekierowania I/O i konfigurację sygnałów definiuje się deklaratywnie w przekazywanych strukturach atrybutów.

#### 4. Przykłady użycia `fork()` bez `execve()`

1. Rozwiązanie problemu n hetmanow
2. fork bomba
3. Chcesz wykonać fragment kodu który może być niestabilny np. może wystąpić dzielenie przez zero
   wtedy niestabilne operacje wykonujemy na forku
4. Odłączenie procesu od terminala wtedy proces wykonuje fork a rodzic od razu robi exit(0)
