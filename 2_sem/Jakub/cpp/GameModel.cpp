#include "GameModel.hpp"
#include "samotnik.hpp" // Include for exception classes
using namespace std::chrono;

GameModel::GameModel()
{
    initializeBoard();
    startTime = steady_clock::now();
}

void GameModel::initializeBoard()
{
    board.resize(7, std::vector<bool>(7, false));
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if ((row >= 2 && row <= 4) || (col >= 2 && col <= 4))
            {
                board[row][col] = true;
            }
        }
    }
    board[3][3] = false;
}

bool GameModel::isPartofBoard(int x, int y) const
{
    return (x >= 2 && x <= 4) || (y >= 2 && y <= 4);
}

bool GameModel::isMoveValid(int x, int y, Kierunek dir) const
{
    if ((!isPartofBoard(x, y)) || (!board[y][x]))
        return false;
    int dx = 0, dy = 0;
    switch (dir)
    {
    case Kierunek::LEWO:
        dx = -1;
        break;
    case Kierunek::PRAWO:
        dx = 1;
        break;
    case Kierunek::GORA:
        dy = -1;
        break;
    case Kierunek::DOL:
        dy = 1;
        break;
    }

    const int jumpedX = x + dx;
    const int jumpedY = y + dy;
    const int targetX = x + 2 * dx;
    const int targetY = y + 2 * dy;

    if (!isPartofBoard(targetX, targetY))
        return false;
    if (jumpedX < 0 || jumpedX > 6 || jumpedY < 0 || jumpedY > 6 || targetX < 0 || targetX > 6 || targetY > 6 || targetY < 0)
        return false;
    return board[jumpedY][jumpedX] && !board[targetY][targetX];
}

void GameModel::move(int x, int y, Kierunek dir)
{
    // Validate coordinates
    if (x < 0 || x >= 7 || y < 0 || y >= 7 || !isPartofBoard(x, y))
    {
        throw nieprawidlowe_wspolrzedne();
    }

    // Check if there's a pawn at the position
    if (!board[y][x])
    {
        throw brak_pionka();
    }

    // Check if the move is valid
    if (!isMoveValid(x, y, dir))
    {
        throw nieprawidlowy_ruch();
    }

    int dx = 0, dy = 0;
    switch (dir)
    {
    case Kierunek::LEWO:
        dx = -1;
        break;
    case Kierunek::PRAWO:
        dx = 1;
        break;
    case Kierunek::GORA:
        dy = -1;
        break;
    case Kierunek::DOL:
        dy = 1;
        break;
    }

    const int jumpedX = x + dx;
    const int jumpedY = y + dy;
    const int targetX = x + 2 * dx;
    const int targetY = y + 2 * dy;
    board[y][x] = false;
    board[jumpedY][jumpedX] = false;
    board[targetY][targetX] = true;
}

int GameModel::numOfPawns() const
{
    int count = 0;
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            if (isPartofBoard(x, y) && board[y][x])
                count++;
        }
    }
    return count;
}

bool GameModel::isEnd() const
{
    if (numOfPawns() == 1)
        return true;

    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            if (board[y][x])
            {
                for (int dir = 0; dir < 4; dir++)
                {
                    if (isMoveValid(x, y, static_cast<Kierunek>(dir)))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
