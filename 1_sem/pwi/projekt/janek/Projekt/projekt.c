#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "biblioteka.h"

#define MAX_TEXT_SIZE 1000000

void wypisanie_statystyk_liter(TextStats stats) {
    // a / A: 63 + 32 = 95 czyli 11% wszystkich liter
    for (int i = 0; i < 26; i++) {
        printf("%c / %c: %i + %i = %i czyli %lf%% wszystkich znaków\n", (char) i+97, (char) i+65, stats.tablica_liter[i],
        stats.tablica_liter[i+26], stats.tablica_liter[i] + stats.tablica_liter[i+26], 
        ((double)stats.tablica_liter[i]+(double)stats.tablica_liter[i+26])/(double)stats.liczba_znakow*100);
    }
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Zbyt mała liczba argumentów\n");
        return 0;
    }

    char text[MAX_TEXT_SIZE] = {0};

    if (argc == 2) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            //perror("Nie można otworzyć pliku");
            strcat(text, argv[1]);
        }
        else {
            fread(text, sizeof(char), MAX_TEXT_SIZE, file);
            fclose(file);
        }
    }
    
    else {
        for (int i = 1; i < argc /*&& argv[i][0] != '['*/; i++) {
            strcat(text, argv[i]);
            if (i < argc - 1) strcat(text, " ");
        }
    }

    TextStats stats;
    statystyki(text, &stats);
    printf("%i\n", stats.liczba_wyrazow);
    printf("%i\n", stats.liczba_znakow);
    printf("%i\n", stats.liczba_liter);
    printf("%i\n", stats.liczba_znakow_specjalnych);

    ignorowanie_wielkosci_liter(text, "jestem");
    //wypisanie_statystyk_liter(stats);
    //podmiana_wzorca(text, "mogła", "liczba", text);
    //printf("%s\n", text);
    //printf("%i\n", zliczanie_wzorca(text, ":"));
    //wyszukiwanie_wzorca(text, "liczba");
    //ignorowanie_wielkosci_liter(text, "jestem");
    return 0;
}