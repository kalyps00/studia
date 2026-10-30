SYSCALL_DEFINE2(kill) -> kill_something_info -> kill_proc_info -> kill_pid_info_type -> group_send_sig_info -> do_send_sig_info -> send_signal_locked -> \_\_send_signal_locked -> complete_signal -> signal_wake_up -> signal_wake_up_state

SYSCALL_DEFINE2(kill, pid_t pid, int sig): Punkt wejścia. Przygotowuje strukturę kernel_siginfo (zawierającą numer sygnału i identyfikator nadawcy) i przekazuje ją dalej

kill_something_info: Pełni rolę rozdzielacza. Ponieważ wysyłamy sygnał do pojedynczego procesu, idziemy warunek if (pid > 0)

kill_pid_info_type: Odpowiada za znalezienie właściwej struktury procesu (task_struct) na podstawie podanego numeru PID przy użyciu funkcji pid_task

do_send_sig_info: safety

\_\_send_signal_locked : To tutaj sygnał jest fizycznie dodawany do procesu. Funkcja sprawdza, czy sygnał nie jest już ignorowany lub zablokowany, alokuje pamięć na element kolejki (strukturę sigqueue) i przypina ten element do listy sygnałów oczekujących (pole pending w task_struct). Następnie wywołuje complete_signal

complete_signal: Przeszukuje wątki należące do procesu, aby znaleźć taki, który nie ma zablokowanego tego sygnału i może go obsłużyć. Gdy go znajdzie, wywołuje funkcję budzącą

signal_wake_up: przygotowanie - flagi i stan

signal_wake_up_state: Kończy ścieżkę dostarczania sygnału przez wywołanie kill. Ustawia w wątku docelowym flagę TIF_SIGPENDING, informując system o nowym oczekującym sygnale do obsłużenia. Następnie próbuje wybudzić proces wywołaniem wake_up_state. Jeśli proces akurat nie spał wywoływane jest kick_process. Jej efektem jest po prostu szturchnięcie procesu, aby natychmiast przerwał to, co aktualnie robi, i zwrócił uwagę na nową flagę TIF_SIGPENDING

sighand - Wskaźnik na strukturę sighand_struct, która zawiera tablicę zdefiniowanych handlerów dla wszystkich sygnałów. Przechowuje informacje o tym, czy dany sygnał ma zostać zignorowany, obsłużony domyślnie przez system, czy też przekazany do własnej funkcji obsługi zdefiniowanej przez program

blocked - Maska sygnałów, czyli zbiór sygnałów aktualnie zablokowanych przez dany wątek. Sygnały znajdujące się w tej masce nie przerywają natychmiast działania procesu, lecz są wstrzymywane do momentu ich odblokowania

pending: Kolejka sygnałów oczekujących (typu struct sigpending), do której trafiają sygnały wysłane do procesu, ale jeszcze mu niedoręczone. Sygnał znajduje się w stanie oczekującym, jeśli np. widnieje w masce blocked lub jeśli wątek nie zdążył jeszcze zostać wybudzony i wrócić do wykonywania instrukcji
