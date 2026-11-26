Struktura danych HTree:

- Flaga w i-węźle: specjalny bit flagi w i-węźle katalogu (EXT2_INDEX_FL) informuje, czy katalog jest indeksowany. Jeśli bit jest zapalony, pierwszy blok katalogu (blok 0) jest interpretowany jako korzeń drzewa HTree.

- Kompatybilność wsteczna: każdy blok indeksu HTree na pierwszych 8 bajtach zawiera pusty wpis katalogowy (fake dirent), przez co dla starszych wersji Linuksa cały blok wygląda jak wolne miejsce. Reszta bloku przechowuje struktury HTree, więc stary sterownik ext2 po prostu omija bloki indeksu i czyta liście jak zwykły katalog.

- Adresowanie logiczne: korzeń to pierwszy blok pliku katalogu, a liście to zwykłe, nieposortowane bloki katalogowe ext2. Wskaźniki w węzłach indeksu to 32-bitowe numery bloków logicznych wewnątrz pliku katalogu (a nie fizyczne numery bloków na dysku), co pozwala nie zmieniać reszty kodu ext2.

- Wpisy indeksu: każdy wpis zajmuje 8 bajtów - składa się z 32-bitowego klucza hasha i 32-bitowego wskaźnika logicznego. Wpisy w bloku indeksu są posortowane rosnąco według klucza hasha. Każdy klucz hasha jest dolnym ograniczeniem (najmniejszym hashem) wpisów w wskazywanym bloku liścia lub poddrzewie. Najmłodszy bit (LSB) klucza hasha służy jako flaga kolizji, więc właściwy hash ma 31 bitów.

- Nagłówek korzenia: blok korzenia zawiera krótki nagłówek (32 bajty) przechowujący głębokość drzewa, ID użytej funkcji hashującej oraz informacje do sprawdzania integralności indeksu.

- Pojemność i głębokość: w bloku 4 KB (po odjęciu 32-bajtowego nagłówka) mieści się do 508 wpisów indeksu. Przy ok. 200 wpisach na liść i 75% zapełnienia jeden poziom indeksu wystarcza na ok. 75 tys. plików, a drugi poziom na ponad 30 milionów plików. Dlatego implementacja obsługuje maksymalnie 2 poziomy indeksu.

Operacja wyszukiwania wpisu o zadanej nazwie (Hash Probe + Entry Lookup):

1. Odczyt korzenia i kontrola spójności (Hash Probe): odczytaj blok 0 katalogu i sprawdź poprawność nagłówka korzenia. Jeśli wykryta zostanie jakakolwiek niespójność, jądro przechodzi awaryjnie (fallback) do zwykłego wyszukiwania liniowego oraz ustawia flagę błędu w superbloku, aby narzędzie fsck mogło później automatycznie odbudować indeks.

2. Obliczenie hasha i zejście w dół: oblicz hash szukanej nazwy (funkcją zapisaną w nagłówku korzenia). Ponieważ wpisy indeksu mają stały rozmiar i są posortowane, wykonaj wyszukiwanie binarne w bieżącym węźle indeksu, aby znaleźć wpis, którego zakres obejmuje szukany hash. Jeśli drzewo ma 2 poziomy, powtórz wyszukiwanie binarne w węźle pośrednim.

3. Łańcuch dostępu (access chain): podczas schodzenia w dół przez węzły indeksu budowany jest łańcuch dostępu (zapamiętana ścieżka od korzenia do liścia, przydatna przy obsłudze kolizji i wstawianiu), po czym wczytywany jest docelowy blok liścia.

4. Przeszukiwanie liścia (Entry Lookup): przeszukaj docelowy blok liścia liniowo (dokładnie tak jak w zwykłym ext2), porównując dokładne nazwy plików. Jeśli znajdziesz nazwę, zwróć wpis.

5. Obsługa kolizji hashów: jeśli nie znaleziono nazwy w liściu, sprawdź w bloku indeksu rodzica, czy klucz hasha następnego liścia ma zapalony najmłodszy bit (bit kolizji). Jeśli tak, porównaj hash szukanej nazwy z hashem następnego liścia (po wyzerowaniu bitu kolizji). Jeśli są równe, wczytaj ten kolejny liść, zaktualizuj access chain i powtórz przeszukiwanie liniowe.

6. Przypadek brzegowy kolizji: jeśli bieżący liść był ostatnim wpisem w swoim bloku indeksu, hash następnika pobierany jest z nadrzędnego bloku indeksu (który jest już w pamięci). Jeśli istnieje możliwość kolizji, przed wczytaniem kolejnego liścia doczytywany jest najpierw kolejny blok indeksu.

7. Koszt operacji: typowo wyszukiwanie wymaga odczytu tylko 2 bloków (indeks + liść), a dla bardzo dużych katalogów 3 bloków.

Wyświetlenie reprezentacji HTree w debugfs:

sudo debugfs -R "htree /var/lib/dpkg/info" /dev/sda4

Co pokazuje wydruk polecenia htree:

- Root node dump - informacje o korzeniu: wersja hasha (Hash Version), liczba poziomów pośrednich (Indirect levels), limit i liczba wpisów w korzeniu (Limit / Count).

- Zakresy hashów dla poszczególnych bloków (np. Entry #0: Hash 0x00000000, block 1; Entry #1: Hash 0x..., block ...).

- Zawartość kolejnych bloków liści (Leaf block ...), wypisującą konkretne nazwy plików, ich wyliczone hashe oraz numery i-węzłów.
