#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
int main()
{
    srand(time(NULL));
    int dl;
    scanf("%d", &dl);
    int S[dl], T[dl], r[1001], P[dl], Q[dl];
    for (int i = 0; i < dl; i++) // wczytanie S
    {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < dl; i++) // wczytanie T
    {
        scanf("%d", &T[i]);
    }
    for (int i = 0; i < 1001; i++) // przy standardowym randzie r[i]= rand() kolizja 99,95%
    {
        r[i] = (rand() << 15) | rand(); // na calym dodatnim incie (prawie) bo rand od 0 -2^15
    }
    P[0] = r[S[0]];
    for (int i = 1; i < dl; i++) // hashe prefixowe S
    {
        P[i] = r[S[i]] ^ P[i - 1];
    }
    Q[0] = r[T[0]];
    for (int i = 1; i < dl; i++) // hashe prefixowe T
    {
        Q[i] = r[T[i]] ^ Q[i - 1];
    }
    int zapytania;
    scanf("%d", &zapytania);
    for (int zapytanie = 0; zapytanie < zapytania; zapytanie++)
    {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        int hash_S, hash_T;
        if (i)
        {
            hash_S = P[i + k] ^ P[i - 1];
        }
        if (j)
        {
            hash_T = Q[j + k] ^ Q[j - 1];
        }
        if (i == 0)
            hash_S = P[k];
        if (j == 0)
            hash_T = Q[k];
        if (hash_S == hash_T)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
}