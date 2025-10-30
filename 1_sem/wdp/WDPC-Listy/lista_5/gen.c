#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_N 80
#define M_PI 3.14159265358979323846

void print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s [n]\n", prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int n = DEFAULT_N;

    // Pobranie argumentu n (jeśli podano)
    if (argc > 2)
    {
        print_usage(argv[0]);
    }
    else if (argc == 2)
    {
        n = atoi(argv[1]);
        if (n <= 0)
        {
            fprintf(stderr, "Invalid value for n: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    // Generowanie wartości funkcji
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        double value = 20 * sin(i * M_PI / 20) + 10; // Skala: 20, przesunięcie: +10
        printf("%.0f\n", round(value));              // Wartości całkowite po zaokrągleniu
    }

    return 0;
}
