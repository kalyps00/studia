#include <stdio.h>
#include <limits.h>
/*
Generalna idea jest taka ze liczy najlespza dorge do kazdego kafelka idac z gory na najpierw po
kolumnach a potem nastepny wiersz i zapisuje tam ile  minimalnie  kary dostac zeby stanac na tym kaflu
wiec konczymy z tablica gdzie na sotatniej kolumnie sa jak dojsc do tego kafla najmniejszym kosztem
i szukamy minimum z tego
*/
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int kafelki[n][m];
    int wagi_sciezek[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &kafelki[i][j]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
            {
                wagi_sciezek[j][i] = kafelki[j][i];
            }
            else
            {
                int min = INT_MAX;
                if (j == 0)
                {
                    if (wagi_sciezek[j][i - 1] < min) // <-
                        min = wagi_sciezek[j][i - 1];
                    if (wagi_sciezek[j + 1][i - 1] < min)
                        min = wagi_sciezek[j + 1][i - 1]; // v
                }
                else if (j == n - 1)
                {
                    if (wagi_sciezek[j][i - 1] < min) // <-
                        min = wagi_sciezek[j][i - 1];
                    if (wagi_sciezek[j - 1][i - 1] < min) // ^
                        min = wagi_sciezek[j - 1][i - 1];
                }
                else
                {
                    if (wagi_sciezek[j - 1][i - 1] < min) // ^
                        min = wagi_sciezek[j - 1][i - 1];
                    if (wagi_sciezek[j][i - 1] < min) // <-
                        min = wagi_sciezek[j][i - 1];
                    if (wagi_sciezek[j + 1][i - 1] < min)
                        min = wagi_sciezek[j + 1][i - 1]; // v
                }
                wagi_sciezek[j][i] = min + kafelki[j][i];
            }
        }
    }

    int wynik = wagi_sciezek[0][m - 1];
    for (int i = 0; i < n; i++)
    {
        if (wagi_sciezek[i][m - 1] < wynik)
            wynik = wagi_sciezek[i][m - 1];
    }
    printf("%d", wynik);
}