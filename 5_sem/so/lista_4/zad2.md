### 1. Czym jest Major i Minor?

Pliki urządzeń w Linuksie (w `/dev`) są tylko punktami dostępu. O tym, z jakim sterownikiem i sprzętem się komunikują, decydują dwie liczby:
- Major (numer główny) identyfikuje konkretny sterownik w jądrze, np. sterownik dysków SCSI. Jądro używa go, żeby przekierować żądanie odczytu lub zapisu do właściwego kodu.
- Minor (numer podrzędny) pozwala sterownikowi rozróżnić konkretne urządzenie, którym zarządza. Jeśli na przykład sterownik (major 8) obsługuje dwa dyski, jeden dostanie minor 0 (`/dev/sda`), a drugi minor 16 (`/dev/sdb`).

### 2. Sposoby przydzielania numerów
- Statycznie: sterownik dostaje konkretny, z góry ustalony numer major, np. z oficjalnej listy. Służy do tego funkcja jądra `register_chrdev_region()`.
- Dynamicznie: sterownik prosi jądro o dowolny wolny numer major, używając funkcji `alloc_chrdev_region()`. Jądro przydziela go w czasie działania.

### 3. Dlaczego alokacja statyczna była w przeszłości wygodniejsza?

W starych systemach UNIX/Linux katalog `/dev/` był zwykłym katalogiem na dysku twardym. Pliki urządzeń tworzono ręcznie za pomocą polecenia `mknod`, wpisując numery major i minor.

Przy alokacji statycznej dany sprzęt miał zawsze ten sam numer major. Administrator tworzył plik przez `mknod` raz i po każdym restarcie komputera plik nadal działał poprawnie.

Przy alokacji dynamicznej po restarcie jądro mogłoby przydzielić sterownikowi inny numer major. Ręcznie utworzone pliki w starym `/dev/` przestałyby wtedy działać, bo wskazywałyby na nieaktualne numery. Trzeba byłoby je naprawiać po każdym uruchomieniu.

Obecnie ten problem nie występuje, ponieważ systemy takie jak `udev` w Linuksie nasłuchują zdarzeń jądra i automatycznie tworzą pliki w wirtualnym katalogu `/dev` (w RAM-ie), używając aktualnych numerów. Dlatego dziś preferuje się alokację dynamiczną, która zmniejsza ryzyko konfliktów numerów.