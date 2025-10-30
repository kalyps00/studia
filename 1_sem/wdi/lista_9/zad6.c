#include <stdio.h>
#include <limits.h>
// Funkcja do obliczenia najmniejszego kosztu ścieżki
int minCostPath(int n, int a[n][n])
{
    int dp[n][n];
    dp[0][0] = a[0][0];         // Zaczynamy od lewego górnego rogu
    for (int j = 1; j < n; j++) // Wypełnianie pierwszego wiersza
    {
        dp[0][j] = dp[0][j - 1] + a[0][j];
    }
    for (int i = 1; i < n; i++) // Wypełnianie pierwszej kolumny
    {
        dp[i][0] = dp[i - 1][0] + a[i][0];
    }
    for (int i = 1; i < n; i++) // Wypełnianie reszty tablicy dp
    {
        for (int j = 1; j < n; j++)
        {
            if (dp[i - 1][j] < dp[i][j - 1])
            {
                dp[i][j] = a[i][j] + dp[i - 1][j];
            }
            else
            {
                dp[i][j] = a[i][j] + dp[i][j - 1];
            }
        }
    }
    return dp[n - 1][n - 1]; // Ostateczny koszt to wartość w prawym dolnym rogu
}

int main()
{
    int n;
    printf("Podaj rozmiar planszy (n): ");
    scanf("%d", &n);

    int a[n][n];
    printf("Podaj koszty odwiedzin pól:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    int result = minCostPath(a, n);
    printf("Najmniejszy koszt ścieżki wynosi: %d\n", result);

    return 0;
}
