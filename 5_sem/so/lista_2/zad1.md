## Stany procesu:

- Running
  - Ready - czeka na przydzial czasu
  - executing
- Interuptible (sen przerywalny) - czeka na np I/O
- Uniteruptible (sen nie przerywalny) - czeka np na odwpowiedz z dysku lub sterownika
- Stopped -Wstrzymany przez np SIGSTOP
- Zombie - zakończył działanie ale czeka na rodzica

Sen przerywalny - czeka na np potok etc. można to przerwać przed oczekiwanym zdarzeniem
Sen nieprzerywalny - proces oczekuje na niskopoziomowy stan sprzętu np odpowiedź kontrolera dysku
i nie można go wybudzić jakiś sygnałem.
Zapobiega to niespojnosci danych jadra/sterownika w przypadku przerwania

## Akcje i zdarzenia wyzwalajace zmiane stanu:

Użytkownik:

- Tworzenie nowego procesu przez np fork() lub clone() (NULL -> Ready)
- Przejscie w Interuptible np przez read() z gniazda(RUnning -> Interuptible)
- Zakończenie działania przez exit() (Running -> Zombie)
- SIGSTOP/SIGCONT wstzrymanie/wznowienie procesu Ready<->Stopped
  Kernel:
- Wybór procesu z kolejki i zmaina jego statusu z Ready na Running
- Skończenie się czasu przydzielonego procesowi i oddanie go innemu wtedy nasz proces executing -> Ready
- Zabicie procesu przez jakis nie obsłużony błąd Running -> Zombie
  Sterowniki:
- Przejscie w stan nieprzerywalny gdy proces musi czekać na ważną operacje sprzętowa
- Wybudzenie z stanu ^

Czy proces może zablokować lub zignorować sygnał `SIGKILL` lub `SIGSEGV`?
SIGKILL się nie da
SIGSEGV da się teoretycznie zignorowac ale przez to że jest to nieprawidłowe odwołanie do pamieci
jak go zigornujemy to wywola się ta sama błędna instrukcja i sie zapętlimy
Proces możemy za to przechwycić i zaimplementować włąsną jego obsługę
