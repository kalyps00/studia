#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    int check = scanf("%i", &n);
    int arr[n + 5];
    // wypelnienie 0
    for (int i = 0; i < n + 5; i++)
        arr[i] = 0;

    // sprawdzenie wejscia
    if (!check || n < 12)
        return 0;
    // liczneie wszystkich trojek do obwod<=n
    for (int i = 1; i < n; i++)
    {
        for (int j = i; (int)sqrt(i * i + j * j) + i + j < n; j++)
        {
            double possible = sqrt(i * i + j * j);
            if (possible == floor(possible))
            {
                int m = i + j + possible;
                arr[m]++;
            }
        }
    }
    // wyznaczenie max
    int max_m = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > arr[max_m])
        {
            max_m = i;
        }
    }
    printf("%i", max_m); // wypisywanie wyniku
}