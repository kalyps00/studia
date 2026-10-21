### Zadanie 4 – Zasoby procesów, stdio i sygnały w fork(2) oraz execve(2)

#### 1. Zasoby dziedziczone przez proces potomny po wywołaniu `fork(2)`

- Deskryptory plików: Wszystkie otwarte deskryptory plików są duplikowane. Zarówno rodzic, jak i dziecko współdzielą te same tablice plików w jądrze, w tym m.in. wspólną pozycję wskaźnika odczytu/zapisu
- Katalog roboczy i główny: Bieżący katalog roboczy (CWD) oraz ewentualnie zmieniony katalog główny (np. przez `chroot`).
- Identyfikatory: Rzeczywiste oraz efektywne identyfikatory użytkownika (UID) i grupy (GID).
- Sygnały: Maska zablokowanych sygnałów oraz pełna dyspozycja sygnałów (własne procedury obsługi i ustawienia ignorowania).
- Środowisko i argumenty: Pełna kopia argumentów wywołania oraz zmiennych środowiskowych procesu macierzystego.
- Limity: Skonfigurowane limity zasobów (np. ustalenia polecenia `ulimit`).
- Pamięć współdzielona: Dołączone segmenty pamięci współdzielonej oraz mapowania pamięci utworzone za pomocą `mmap`.

#### 2. Zasoby przekazywane do nowego programu po wywołaniu `execve(2)`

- Argumenty wywołania i środowisko w postaci tablicy argumentów argv oraz tablicy środowiskowej envp
- Deskryptory plików: Deskryptory otwarte przed wywołaniem `execve` pozostają otwarte i dostępne dla nowego programu, z wyjątkiem tych, dla których włączono flagę `O_CLOEXEC` (Close-on-Exec)
- Identyfikatory procesu: PID oraz numer procesu macierzystego (PPID) pozostają takie same
- Katalog roboczy i limity - nowy program zachowuje bieżący katalog roboczy oraz zdefiniowane ograniczenia zasobów.

#### 3. Czemu przed wywołaniem `fork` należy opróżnić bufory biblioteki `stdio(3)`?

Bufory biblioteki standardowego wejścia/wyjścia np dla funkcji `printf` są zarządzane w przestrzeni użytkownika, a nie bezpośrednio w jądrze systemu co za tym idzie wywołując fork proces dziecko dostanie wszystko co jest w buforze rodzica do swojego własnego bufora

W rezultacie, gdy oba procesy w końcu zrzucą swoje bufory te same dane zostaną wydrukowane podwójnie. Aby temu zapobiec przed fork() wywołuje się `fflush(NULL)`

#### 4. Co jądro robi w trakcie wywołania `execve` z konfiguracją procedur obsługi sygnałów?

Podczas `execve(2)` jądro całkowicie zwalnia dotychczasową przestrzeń adresową procesu i ładuje w jej miejsce nowy kod. Pociąga to za sobą zmianę w konfiguracji sygnałów:

1.  Sygnały ignorowane (`SIG_IGN`): Pozostają zignorowane przez nowy program (są dziedziczone).
2.  Sygnały z niestandardowymi procedurami obsługi: Jądro przywraca dla nich akcję domyślną (`SIG_DFL`) bo skoro niszczyczmy stara przestrzen adresowa to nie ma co szukać skoku do handlera
