#include <stdio.h>
// Colatz problem 3x+1

int main()
{
    int n, m, d, ilosc_kaktosow = 0;
    unsigned long long suma = 0, max_suma = 0;
    scanf("%d%d%d", &n, &m, &d);
    int cykl_kaktusow[n][m];
    int cykliczne = 0;
    unsigned long long wysokosc[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cykl_kaktusow[i][j] = 0;
            scanf("%llu", &wysokosc[i][j]);
            if (wysokosc[i][j])
            {
                ilosc_kaktosow++;
                if (wysokosc[i][j] == 1 ||
                    wysokosc[i][j] == 2 ||
                    wysokosc[i][j] == 4)
                {
                    cykliczne++;
                    cykl_kaktusow[i][j] = 1;
                }
            }
            suma += wysokosc[i][j];
        }
    }
    max_suma = suma;
    int braked = 1;
    for (int dzien = 0; dzien < d && braked; dzien++) // dni
    {

        int grzadki_do_zmiany = dzien % n;
        if (cykliczne == ilosc_kaktosow)
        {
            if (max_suma >= (unsigned long long)n * m * 4)
            {
                braked = 0;
                break;
            }
        }
        for (int grzadka = 0; grzadka <= grzadki_do_zmiany; grzadka++)
        {
            for (int numer_kaktusa = 0; numer_kaktusa < m; numer_kaktusa++)
            {
                if (wysokosc[grzadka][numer_kaktusa] > 0)
                {

                    suma -= wysokosc[grzadka][numer_kaktusa];
                    if (wysokosc[grzadka][numer_kaktusa] % 2 == 0) // h/2
                    {
                        wysokosc[grzadka][numer_kaktusa] /= 2;
                    }
                    else // 3h+1
                    {
                        wysokosc[grzadka][numer_kaktusa] = 3 * wysokosc[grzadka][numer_kaktusa] + 1;
                    }

                    if (wysokosc[grzadka][numer_kaktusa] == 1 ||
                        wysokosc[grzadka][numer_kaktusa] == 2 ||
                        wysokosc[grzadka][numer_kaktusa] == 4)
                    {
                        if (cykl_kaktusow[grzadka][numer_kaktusa] == 0)
                        {
                            cykliczne++;
                            cykl_kaktusow[grzadka][numer_kaktusa] = 1;
                        }
                    }
                    suma += wysokosc[grzadka][numer_kaktusa];
                }
            }
        }
        if (suma > max_suma)
        {
            max_suma = suma;
        }
    }
    printf("%llu", max_suma);
}