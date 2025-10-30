#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <vector>
#include <chrono>

enum class Kierunek
{
    LEWO,
    PRAWO,
    GORA,
    DOL
};

class GameModel
{
private:
    std::vector<std::vector<bool>> board;
    std::chrono::steady_clock::time_point startTime;
    bool isPartofBoard(int x, int y) const;

public:
    GameModel();
    void initializeBoard();
    bool isMoveValid(int x, int y, Kierunek dir) const;
    // This function now throws exceptions for invalid moves
    void move(int x, int y, Kierunek dir);
    int numOfPawns() const;
    bool isEnd() const;
    const std::vector<std::vector<bool>> &getBoard() const { return board; }
    std::chrono::steady_clock::time_point getStartTime() const { return startTime; }
};

#endif // GAME_MODEL_HPP
