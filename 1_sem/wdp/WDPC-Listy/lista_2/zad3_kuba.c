#include <stdio.h>

long long wys[155][205];

void zwieksz(int n, int m)
{
    if (wys[n][m] % 2 == 0)
    {
        wys[n][m] /= 2;
    }
    else
        wys[n][m] = 3 * wys[n][m] + 1;
}

int main()
{
    int d = 0, n = 0, m = 0;
    scanf("%d%d%d", &n, &m, &d);
    long long suma = 0, makssuma = 0;
    long long wysokosc = 0;
    int ilekaktusow = 0;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            scanf("%lld", &wysokosc);
            suma += wysokosc;
            if (wysokosc != 0)
                ilekaktusow++;
            wys[i][j] = wysokosc;
        }
    }
    makssuma = suma;
    int flaga = 0;
    int zacyklone = 0;
    for (int z = 0; z < d; z++)
    {
        suma = 0;
        if (flaga == 1)
            zacyklone = -5;
        else
            zacyklone = 0;

        int ile = z % n;
        for (int i = 0; i <= ile; i++)
        {
            for (int j = 0; j < m; j++)
            {
                zwieksz(i, j);
                if (wys[i][j] == 1 || wys[i][j] == 2 || wys[i][j] == 4)
                {
                    zacyklone++;
                }
                suma += wys[i][j];
            }
        }

        for (int i = ile + 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (wys[i][j] == 1 || wys[i][j] == 2 || wys[i][j] == 4)
                {
                    zacyklone++;
                }
                suma += wys[i][j];
            }
        }

        if (suma > makssuma)
        {
            makssuma = suma;
        }
        if (zacyklone == ilekaktusow)
        {
            d = z + 3 * n;
            flaga = 1;
            if (makssuma > 4 * n * m)
                break;
        }
    }

    printf("%lld", makssuma);
}