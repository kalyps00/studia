#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    int k = atoi(argv[1]);
    float a[k + 1], f[n + 1];
    if (argc != (2 * k + 2) || n < 0 || n < k)
    {
        printf("Nieprawidłowe argumenty]");
        return 1;
    }

    for (int i = 1; i <= k; i++)
    {
        a[i - 1] = atof(argv[i + 1]);
    }

    for (int i = k + 1; i < 2 * k + 1; i++)
    {
        f[i - k - 1] = atof(argv[i + 1]);
    }

    int count = 0;

    for (int i = k; i <= n; i++)
    {
        count = 0;
        for (int j = i - 1; j >= i - k; j--)
        {

            f[i] += (a[count] * f[j]);
            count++;
        }
    }
    printf("%f", f[n]);
}