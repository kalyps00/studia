#include <stdio.h>

void hanoi(int n, char zrodlo, char cel, char pomoc)
{
    if (n == 1)
    {
        printf("Przenieś dysk 1 z wieży %c na wieżę %c\n", zrodlo, cel);
        return;
    }

    hanoi(n - 1, zrodlo, pomoc, cel); // Przenieś n-1 dysków na wieżę pomocniczą
    printf("Przenieś dysk %d z wieży %c na wieżę %c\n", n, zrodlo, cel);
    hanoi(n - 1, pomoc, cel, zrodlo); // Przenieś n-1 dysków na wieżę docelową
}

int main()
{
    int n; // Liczba dysków

    printf("Podaj liczbę dysków: ");
    scanf("%d", &n);

    printf("Kroki przenoszenia %d dysków:\n", n);
    hanoi(n, 'A', 'C', 'B'); // A: źródło, C: cel, B: pomocnicza

    return 0;
}
