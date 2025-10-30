#include "wiersze.h"
Wiersz *nowy()
{
    Wiersz *w = (Wiersz *)malloc(sizeof(Wiersz));
    if (w == NULL)
        return NULL;
    w->slowa = NULL;
    w->ilosc_slow = 0;
    w->bufor_slow = 0;
    return w;
}
void wypisz(Wiersz *w)
{
    for (int i = 0; i < w->ilosc_slow; i++)
    {
        if (w->slowa[i] != NULL)
            printf("%s ", w->slowa[i]);
    }
    printf("\n");
}
void zwolnij_wiersz(Wiersz *w)
{
    if (w != NULL)
    {
        for (int i = 0; i < w->ilosc_slow; i++)
        {
            free(w->slowa[i]);
        }
        free(w->slowa);
        free(w);
    }
}

void dodajslowo(Wiersz *w, char *slowo)
{
    if (w->ilosc_slow >= w->bufor_slow)
    {
        char **noweslowo = realloc(w->slowa, (w->ilosc_slow * 2) * sizeof(char *));
        if (noweslowo == NULL)
        {
            // printf("Blad alokacji pamieci przy dodawaniu slowa.\n");
            zwolnij_wiersz(w);
            return;
        }
        w->slowa = noweslowo;
        w->bufor_slow = w->ilosc_slow * 2;
    }
    size_t dlslowa = strlen(slowo) + 1;
    w->slowa[w->ilosc_slow] = (char *)malloc(dlslowa);
    if (w->slowa[w->ilosc_slow] == NULL)
    {
        // printf("Blad alokacji pamieci przy dodawaniu slowa.\n");
        zwolnij_wiersz(w);
        return;
    }
    strcpy(w->slowa[w->ilosc_slow], slowo);
    w->ilosc_slow++;
}

char *readline() // zwraca wczytana linie jako char* null terminated
{
    size_t rozmiarbufora = 64;
    char *bufor = (char *)malloc(rozmiarbufora);
    if (bufor == NULL)
    {
        // mozliwe jest ze program wczyta tylko tyle lini ile moze
        return NULL;
    }
    char c;
    size_t pos = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (pos + 1 >= rozmiarbufora) // +1 bo trzeba dodac \0
        {
            rozmiarbufora *= 2;
            char *tempbufor = realloc(bufor, rozmiarbufora);
            if (tempbufor == NULL) // wyejbka i null rob dalej ale juz miejsa nie ma
            {
                free(bufor);
                return NULL;
            }
            bufor = tempbufor;
        }
        bufor[pos] = c;
        pos++;
    }
    if (pos == 0 && c == EOF) // koniec wejscia
    {
        free(bufor);
        return NULL;
    }

    bufor[pos] = '\0';
    return bufor;
}

Wiersz *podzial(char *linia) // zwraca poinert na nowy wiersz podzielony na slowa
{
    Wiersz *nowy_wiersz = nowy();
    if (nowy_wiersz == NULL)
    {
        return NULL;
    }
    size_t buforslowa = 20; // zakladam ze slowo ma max 20  znakow
    char *slowo = malloc(buforslowa);
    if (slowo == NULL)
    {
        zwolnij_wiersz(nowy_wiersz);
        return NULL;
    }

    size_t dlugoscslowa = 0;
    for (int i = 0; linia[i] != '\0'; i++)
    {
        if (isgraph(linia[i])) // Znak drukowalny czyli kawalek slowa
        {
            if (dlugoscslowa + 1 >= buforslowa) // nie umiem zakladac dlugosciu slowa
            {
                buforslowa *= 2;
                char *tempslowo = realloc(slowo, buforslowa);
                if (tempslowo == NULL)
                {
                    free(slowo);
                    zwolnij_wiersz(nowy_wiersz);
                    return NULL;
                }
                slowo = tempslowo;
            }
            slowo[dlugoscslowa] = linia[i];
            dlugoscslowa++;
        }
        else if (dlugoscslowa > 0) // Koniec słowa
        {
            slowo[dlugoscslowa] = '\0';
            dodajslowo(nowy_wiersz, slowo);
            dlugoscslowa = 0;
        }
    }
    // Dodaj ostatnie słowo, jeśli istnieje
    if (dlugoscslowa > 0)
    {
        slowo[dlugoscslowa] = '\0';
        dodajslowo(nowy_wiersz, slowo);
    }
    free(slowo);
    // zwolnienie nadprograomo przypisanej ilosci potencjanlych slow
    while (nowy_wiersz->ilosc_slow < nowy_wiersz->bufor_slow)
    {
        free(nowy_wiersz->slowa[nowy_wiersz->bufor_slow]);
        nowy_wiersz->bufor_slow--;
    }
    return nowy_wiersz;
}
void sort(Wiersz **tablica, size_t n, comparator comparator_f)
{
#ifdef USE_QSORT
    qsort(tablica, n, sizeof(Wiersz *), (int (*)(const void *, const void *))comparator_f);
#else
    int swapped;
    for (size_t i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (comparator_f(tablica[j], tablica[j + 1]) > 0)
            {
                Wiersz *temp = tablica[j];
                tablica[j] = tablica[j + 1];
                tablica[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
#endif
}
int komperator(const Wiersz *w1, const Wiersz *w2)
{
    int dlugosc1 = w1->ilosc_slow - 1; // Indeksy od 0
    int dlugosc2 = w2->ilosc_slow - 1;
    while (dlugosc1 >= 0 && dlugosc2 >= 0)
    {
        int val = strcmp(w1->slowa[dlugosc1], w2->slowa[dlugosc2]);
        if (val != 0)
        {
            return val; // strcmp zwraca -1, 0, lub 1
        }
        dlugosc1--;
        dlugosc2--;
    }

    // Jeśli doszliśmy tutaj, jedna z tablic skończyła się
    if (dlugosc1 < 0 && dlugosc2 < 0)
        return 0; // Obie równe
    if (dlugosc1 < 0)
        return -1; // w1 jest "mniejszy"
    return 1;      // w2 jest "mniejszy"
}
