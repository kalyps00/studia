Zadanie 6 – flagi wywołania systemowego open(2):

Dopisywanie komunikatów diagnostycznych z wielu procesów bez wyścigów:
O_APPEND (wraz z O_WRONLY lub O_RDWR) – jądro atomowo przesuwa kursor na sam koniec pliku przed każdym wywołaniem write(2), więc procesy nie nadpisują sobie nawzajem danych.

Nowy program nie może otrzymać otwartego pliku po execve(2):
O_CLOEXEC – atomowo ustawia na deskryptorze flagę close-on-exec (FD_CLOEXEC), dzięki czemu jądro automatycznie zamyka ten deskryptor podczas wywołania execve(2).

Umożliwienie otwarcia nowego pliku dopiero po zakończeniu zapisu:
O_TMPFILE (wymaga O_WRONLY lub O_RDWR i podania ścieżki do katalogu zamiast pliku) – tworzy nienazwany, niewidoczny w systemie plików i-węzeł. Dopiero po zakończeniu zapisu można go „upublicznić” (nadać mu nazwę) atomowym wywołaniem linkat(2) (np. na ścieżce /proc/self/fd/<fd>).

Istnienie pliku jako blokada na współdzielony zasób:
O_CREAT | O_EXCL – jądro atomowo sprawdza, czy plik istnieje, i tworzy go tylko wtedy, gdy go nie ma. Jeśli plik już istnieje (blokada jest zajęta), open(2) kończy się błędem EEXIST.
