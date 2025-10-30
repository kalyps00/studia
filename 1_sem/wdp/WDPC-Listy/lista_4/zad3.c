#include <stdio.h>

void dzielniki(int pierwsze[], int n)
{
    for (int i = 2; i < n; i++)
    {
        int liczba = i;
        int wynik = 0;
        for (int j = 2; j * j <= liczba; j++)
        {
            while (liczba % j == 0)
            {
                wynik++;
                liczba /= j;
            }
        }
        if (liczba > 1)
        {
            wynik++;
        }
        pierwsze[i] = wynik;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int pierwsze[n];
    dzielniki(pierwsze, n);

    int wynik = 0;

    for (int a = 2; a < n; a++)
    {
        if (pierwsze[a] == 1)
        {
            for (int b = 2; b < n - a; b++)
            {
                if (pierwsze[b] == 5)
                {
                    int c = n - a - b;
                    if (c > 1 && pierwsze[c] == 7)
                    {
                        wynik++;
                    }
                }
            }
        }
    }

    printf("%d\n", wynik);
    return 0;
}
