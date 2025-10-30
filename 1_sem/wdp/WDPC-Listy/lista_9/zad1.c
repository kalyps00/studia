#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wiersze.h"
int main()
{
    size_t ilosc_wierszy = 0;
    size_t rozmiar_tablicy = 8;

    Wiersz **wejscie = malloc(sizeof(Wiersz *) * rozmiar_tablicy);
    if (wejscie == NULL)
    {
        printf("alokacja nieudana");
        return 1;
    }
    char *linia;
    while ((linia = readline()) != NULL)
    {
        if (ilosc_wierszy >= rozmiar_tablicy) // powiększamy tablicę w razie potrzeby
        {
            rozmiar_tablicy *= 2;
            Wiersz **temp = realloc(wejscie, sizeof(Wiersz *) * rozmiar_tablicy);
            if (temp == NULL)
            {
                printf("re-alokacja nieudana");
                free(linia);
                for (size_t i = 0; i < ilosc_wierszy; i++)
                    zwolnij_wiersz(wejscie[i]);
                free(wejscie);
                return 1;
            }
            wejscie = temp;
        }

        wejscie[ilosc_wierszy] = podzial(linia);
        ilosc_wierszy++;
        free(linia);
    }
    while (rozmiar_tablicy > ilosc_wierszy)
    {
        zwolnij_wiersz(wejscie[rozmiar_tablicy]);
        rozmiar_tablicy--;
    }
    printf("\nposortowane:\n");
    // sortowanie
    sort(wejscie, ilosc_wierszy, komperator);
    for (size_t i = 0; i < ilosc_wierszy; i++)
    {
        wypisz(wejscie[i]);
        zwolnij_wiersz(wejscie[i]);
    }
    free(wejscie);
    return 0;
}
