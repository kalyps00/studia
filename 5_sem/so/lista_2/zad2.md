### Różnice w tworzeniu procesów w systemie Linux i Windows

Linux:

- Tworzenie procesu jest rozdzielone na dwa osobne wywołania systemowe: `fork()` i `execve()`.
- Proces jest najpierw klonowany (dziedzicząc stan rodzica), a następnie zastępuje swoją przestrzeń adresową nowym kodem binarnym przy pomocy wywołania `execve()`.

Windows:

- Tworzenie procesu jest jednoetapowe przy pomocy funkcji `CreateProcess()`.
- `CreateProcess()` od razu tworzy proces i jego pierwszy wątek.
- Nowy proces nie jest klonem rodzica (jak w przypadku `fork()`), tylko zupełnie nowym procesem, co za tym idzie wymaga podania wielu argumentów podczas tworzenia

---

### Przebieg instrukcji `fork(2)` i `execve(2)`

**Akcje w trakcie obsługi `fork(2)`:**

1. Alokujemy nowe `task_struct` dla dziecka, a następnie przypisujemy mu nowy PID oraz nowy stos jądra
2. Kopiowanie rejestrów procesora rodzica
3. Kopiowanie i współdzielenie zasobów jądra, takich jak otwarte deskryptory plików, sygnały czy limity systemowe w efekcie dziecko i rodzic wskazują na te same obiekty plików
4. Kopiowanie tablic stron pamięci w trybie **Copy-on-Write (CoW)** - przestrzeń adresowa nie jest fizycznie duplikowana od razu strony są współdzielone jako "tylko do odczytu", dopóki któryś z procesów nie spróbuje do nich zapisać
5. Dodanie naszego nowego procesu do kolejki procesów gotowych do wykonania przez scheduler
6. Zwrócenie PID dziecka do procesu macierzystego oraz wartości 0 do procesu potomnego (dzięki temu proces wie, czy jest rodzicem, czy dzieckiem)

**Akcje w trakcie obsługi `execve(2)`:**

1. Sprawdzenie uprawnień dostępu do podanego pliku binarnego oraz odczytanie jego formatu (np. ELF żeby sprawdzić jak załadować program do pamięci)
2. Zwolnienie przestrzeni adresowej procesu potomnego
3. Załadowanie nowego kodu, danych i sekcji BSS z pliku wykonywalnego do nowej przestrzeni adresowej
4. Przygotowanie nowego stosu trybu użytkownika i umieszczenie na nim przekazanych argumentów argv
5. Ustawienie rejestrów procesora w stan początkowy, w tym wskaźnika instrukcji (Program Counter) na entry point nowego programu.

---

### Dlaczego zamiana fork i execve na jedno wywołanie spawn rodzi problemy?

Gdyby istniało tylko wywołanie `spawn`:
Proces byłby tworzony i od razu uruchamiany z nowym kodem. Powłoka nie miałaby możliwości wstawienia własnego kodu pomiędzy utworzeniem procesu a uruchomieniem w nim programu, aby przekierować jego deskryptory. Aby to obsłużyć trzeba by bylo mase argumentów opisujących wyjścia wejscia
