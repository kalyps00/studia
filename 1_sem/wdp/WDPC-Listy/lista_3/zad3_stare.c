#include <stdio.h>
#include <limits.h>

int num37(int num)
{
    int flag_seven = 0, flag_three = 0;
    while (num)
    {
        if (num % 10 == 7)
            flag_seven = 1;
        else if (num % 10 == 3)
            flag_three = 1;
        num /= 10;
    }
    return flag_seven && flag_three;
}

int prime(int num)
{
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, m, v;
    scanf("%d%d%d", &n, &m, &v);

    int tab[m - n + 1];
    int ind = -1; // zmiana

    for (int i = n; i <= m; i++)
    {
        if (prime(i) && num37(i))
        {
            ind++;
            tab[ind] = i;
        }
    }
    int lastsuma = tab[ind] + tab[ind - 1];
    int sum[10000000] = {}; // na ile psosobow suma
    for (int i = 0; i < ind; i++)
    {
        for (int j = i + 1; j < ind; j++)
        {
            sum[tab[i] + tab[j]]++;
        }
    }
    int min_result = INT_MAX;
    int j = 0;
    for (int i = 0; i < lastsuma; i++)
    {
        if (i - tab[j + 1] > v)
            j++;
        if (sum[i] == 1 && min_result > i - tab[j] && i - tab[j] > v)
        {

        } // czy ta liczba ktora spelnia i - tab[j] nie jest jedna z liczb z sumy
        min_result = i - tab[j];
        if (sum[i] > 1 && min_result > i - tab[j] && i - tab[j] > v)
            min_result = i - tab[j];
    }

    printf("%d", min_result);
    return 0;
}