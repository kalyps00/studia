#include <stdio.h>
#include <stdbool.h>

#define N 8 // Rozmiar szachownicy 8x8

// Tablica reprezentująca ruchy skoczka
int moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

// Funkcja sprawdzająca, czy dane pole jest w zakresie planszy
bool isSafe(int x, int y, int board[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Funkcja rekurencyjna rozwiązująca problem
bool solveKnightTour(int n, int board[N][N], int curr_x, int curr_y, int moveCount)
{
    if (moveCount == n * n)
    {
        return true; // Wszystkie pola zostały odwiedzone
    }

    for (int i = 0; i < 8; i++)
    {
        int new_x = curr_x + moves[i][0];
        int new_y = curr_y + moves[i][1];

        if (isSafe(new_x, new_y, board))
        {
            board[new_x][new_y] = moveCount; // Oznaczamy pole jako odwiedzone
            if (solveKnightTour(n, board, new_x, new_y, moveCount + 1))
            {
                return true;
            }
            board[new_x][new_y] = -1; // Cofamy ruch (backtracking)
        }
    }
    return false;
}

// Funkcja rozwiązująca problem dla danej szachownicy
void knightTour()
{
    int board[N][N];

    // Inicjalizacja szachownicy, wszystkie pola są ustawione na -1 (nieodwiedzone)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = -1;
        }
    }

    // Rozpoczynamy od pierwszego pola (0, 0)
    board[0][0] = 0;

    // Uruchamiamy algorytm
    if (solveKnightTour(N, board, 0, 0, 1))
    {
        // Wypisanie rozwiązania
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%2d ", board[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Nie ma rozwiązania dla tego problemu.\n");
    }
}

int main()
{
    knightTour();
    return 0;
}
