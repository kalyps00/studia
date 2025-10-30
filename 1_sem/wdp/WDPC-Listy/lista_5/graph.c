#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HEIGHT 100

void print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s [-b] [-m SYMBOLS]\n", prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int border = 0;            // Flaga obramowania
    char symbols[6] = "#=|+-"; // Domyślne symbole
    char *custom_symbols = NULL;

    // Parsowanie argumentów
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            border = 1;
        }
        else if (strcmp(argv[i], "-m") == 0)
        {
            if (i + 1 >= argc || (strlen(argv[i + 1]) != 2 && strlen(argv[i + 1]) != 5))
            {
                fprintf(stderr, "Invalid -m argument\n");
                exit(EXIT_FAILURE);
            }
            custom_symbols = argv[++i];
        }
        else
        {
            print_usage(argv[0]);
        }
    }

    // Ustawienie symboli, jeśli podano -m
    if (custom_symbols)
    {
        strncpy(symbols, custom_symbols, strlen(custom_symbols));
    }

    // Odczyt danych ze standardowego wejścia
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    int values[n];
    int max_value = 0, min_value = 0;

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &values[i]) != 1)
        {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
        if (values[i] > max_value)
            max_value = values[i];
        if (values[i] < min_value)
            min_value = values[i];
    }

    int range = max_value - min_value;
    if (range == 0)
        range = 1;

    // Drukowanie wykresu
    for (int y = max_value; y >= min_value; y--)
    {
        if (border && y == max_value)
            printf("%c", symbols[3]);
        else if (border)
            printf("%c", symbols[2]);

        for (int x = 0; x < n; x++)
        {
            if (values[x] == y)
            {
                printf("%c", symbols[0]);
            }
            else if (y == 0)
            {
                printf("%c", symbols[1]);
            }
            else
            {
                printf(" ");
            }
        }

        if (border)
            printf("%c", symbols[2]);
        printf("\n");
    }

    if (border)
    {
        printf("%c", symbols[4]);
        for (int i = 0; i < n; i++)
            printf("%c", symbols[1]);
        printf("%c\n", symbols[4]);
    }

    return 0;
}
