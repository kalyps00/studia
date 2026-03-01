#include <stdio.h>

int main(void)
{
    // 0 (NUL) - Terminator ciągu znaków
    // Napis kończy się na pierwszym '\0', reszta tablicy jest ignorowana przez printf
    char null_test[] = {'A', 'B', 'C', '\0', 'D', 'E', 'F'};
    printf("NUL test: %s\n", null_test);

    // 7 (BEL) - Sygnał dźwiękowy/alert
    // Może wydać dźwięk "beep" lub spowodować mignięcie terminala
    printf("BEL test: Wysyłam sygnał dźwiękowy...\a\n");

    // 10 (LF) - Nowa linia
    // Standardowe przejście do kolejnego wiersza
    printf("LF test: Linia pierwsza.\nLinia druga.\n");

    // 12 (FF) - Form Feed (Wysuw strony / Czyszczenie ekranu)
    // W nowoczesnych terminalach często działa jak komenda 'clear'
    printf("Naciśnij Enter, aby przetestować FF (może wyczyścić ekran)...");
    getchar();
    printf("\f");

    // 4 (EOT) - End of Transmission
    // Zazwyczaj nie jest drukowalny, służy do zamykania strumieni (np. Ctrl+D w Linux)
    printf("EOT (kod 4) ma wartość dziesiętną: %d\n", 4);

    return 0;
}