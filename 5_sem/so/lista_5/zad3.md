## Czemu nie można czytać i modyfikować katalogów przez read(2) i write(2)?

write ->
Katalogi przechowują kluczowe metadane systemu plików (mapowania nazw na i-węzły). Gdyby proces użytkownika mógł pisać do katalogu dowolne bajty, łatwo mógłby uszkodzić spójność systemu plikó

read ->
Sposób fizycznego zapisu katalogu na dysku zależy od konkretnego systemu plików np. ext4, XFS, Btrfs, FAT . Zwykłe read(2) zwracałoby surowe, nieczytlene bajty zależne od implementacji.

## Jakim wywołaniem systemowym można wczytać rekord katalogu?

Służy do tego wywołanie systemowe getdents64(2) lub getdents(2)
które zwraca rekordy katalogu w ujednoliconym, niezależnym od systemu plików formacie struktur, w c możemy użyć funkcji readdir(3)

## Dlaczego zawartość katalogu nie jest posortowana?

Głownie z celow wydajnosciowych
jadro wrzuca nowe wpisy tam gdzie jest miejsce albo tam gdzie np by wskazywala jakas funkcja hashujaca

stat /

2+ liczba katalogów (bez symlinkow) 2 bo /. i /..
