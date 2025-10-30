#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funkcja do liczenia liczby dzielników
unsigned liczba_dzielnikow(unsigned long n)
{
    unsigned long count = 0;
    for (unsigned long i = 1; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            count += 2; // i oraz n/i są dzielnikami
            if (i * i == n)
            {
                count--; // Jeśli i * i == n, doliczono dzielnik podwójnie
            }
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Nieprawidłowa ilość argumentów\n");
        return 1;
    }

    char *endptr;
    unsigned long n = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Konwersja nieudana\n");
        return 1;
    }

    unsigned long liczba_trojkatna = 0;
    unsigned long i = 1;

    while (1)
    {
        liczba_trojkatna += i; // T_n = T_(n-1) + n
        unsigned long dzielniki = liczba_dzielnikow(liczba_trojkatna);
        if (dzielniki > n)
        {
            printf("Indeks: %lu, liczba trójkątna: %lu\n",
                   i, liczba_trojkatna);
            break;
        }
        i++;
    }

    return 0;
}
