#include <stdio.h>
#include <stdbool.h>
int magicSum(int n)
{
    return n * (n * n + 1) / 2;
}

// Funkcja sprawdzająca, czy tablica jest poprawnym kwadratem magicznym
bool isMagicSquare(int n, int grid[n][n])
{
    int sum = magicSum(n);

    // Sprawdzamy wiersze
    for (int i = 0; i < n; i++)
    {
        int rowSum = 0;
        for (int j = 0; j < n; j++)
        {
            rowSum += grid[i][j];
        }
        if (rowSum != sum)
            return false;
    }

    // Sprawdzamy kolumny
    for (int j = 0; j < n; j++)
    {
        int colSum = 0;
        for (int i = 0; i < n; i++)
        {
            colSum += grid[i][j];
        }
        if (colSum != sum)
            return false;
    }

    // Sprawdzamy przekątne
    int diag1Sum = 0, diag2Sum = 0;
    for (int i = 0; i < n; i++)
    {
        diag1Sum += grid[i][i];
        diag2Sum += grid[i][n - i - 1];
    }

    if (diag1Sum != sum || diag2Sum != sum)
        return false;

    return true;
}

// Funkcja do przeszukiwania z nawrotami
bool solveMagicSquare(int n, int grid[n][n], int num, int visited[n * n])
{
    if (num > n * n)
    {
        return isMagicSquare(n, grid);
    }

    int x = (num - 1) / n;
    int y = (num - 1) % n;

    for (int val = 1; val <= n * n; val++)
    {
        // Sprawdzamy, czy liczba jest już użyta
        if (visited[val] == 1)
            continue;
        grid[x][y] = val;
        visited[val] = 1;

        if (solveMagicSquare(n, grid, num + 1, visited))
        {
            return true;
        }

        grid[x][y] = 0;   // Cofamy ruch
        visited[val] = 0; // jednak nie uzylismy tej liczby
    }
    return false;
}

// Funkcja rozwiązująca problem
void magicSquare(int n, int grid[n][n], int visited[n * n])
{

    if (solveMagicSquare(n, grid, 1, visited))
    {
        printf("Kwadrat magiczny %d x %d:\n", n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%2d ", grid[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Nie ma rozwiązania dla tego kwadratu magicznego.\n");
    }
}

int main()
{
    int n;
    printf("Podaj rozmiar kwadratu magicznego (n): ");
    scanf("%d", &n);

    if (n < 3)
    {
        printf("Kwadrat magiczny nie istnieje dla tego rozmiaru.\n");
    }
    else
    {
        int grid[n][n];
        int visited[n * n];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                grid[i][j] = 0;
                visited[i * j] = 0;
            }
        }
        magicSquare(n, grid, visited);
    }

    return 0;
}
