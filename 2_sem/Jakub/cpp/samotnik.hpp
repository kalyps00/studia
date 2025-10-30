#ifndef SAMOTNIK_HPP
#define SAMOTNIK_HPP

#include "GameModel.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <chrono>

class wyjatek_samotnika : public std::logic_error
{
public:
    explicit wyjatek_samotnika(const std::string &msg) : std::logic_error(msg) {}
};

class nieprawidlowe_polecenie : public wyjatek_samotnika
{
public:
    nieprawidlowe_polecenie() : wyjatek_samotnika("Nieprawidlowy format polecenia") {}
};

class nieprawidlowe_wspolrzedne : public wyjatek_samotnika
{
public:
    nieprawidlowe_wspolrzedne() : wyjatek_samotnika("Podano nieprawidlowe wspolrzedne") {}
};

class brak_pionka : public wyjatek_samotnika
{
public:
    brak_pionka() : wyjatek_samotnika("Na podanym polu nie ma pionka") {}
};

class nieprawidlowy_ruch : public wyjatek_samotnika
{
public:
    nieprawidlowy_ruch() : wyjatek_samotnika("Podany ruch jest nieprawidlowy") {}
};

class ConsoleView
{
public:
    void drawBoard(const std::vector<std::vector<bool>> &board);
    void printMistake(const std::string &msg);
    void printStats(int pawns, const std::chrono::seconds &time);
    void showEnd(bool win);
};

struct ParsedMove
{
    int x, y;
    Kierunek dir;
};

class GameController
{
private:
    GameModel model;
    ConsoleView view;
    ParsedMove parseInput(const std::string &input) const;
    std::chrono::seconds countGameTime() const;

public:
    void start();
    void restartGame();
};

#endif