#include "samotnik.hpp"
#include "GameModel.hpp"
#include <iostream>
#include <cctype>
using namespace std::chrono;

void ConsoleView::drawBoard(const std::vector<std::vector<bool>> &board)
{
    std::cout << "  A B C D E F G\n";
    for (int row = 0; row < 7; row++)
    {
        std::cout << (row + 1) << " ";
        for (int col = 0; col < 7; col++)
        {
            if ((row >= 2 && row <= 4) || (col >= 2 && col <= 4))
            {
                std::cout << (board[row][col] ? 'O' : '.') << " ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}

void ConsoleView::printMistake(const std::string &msg)
{
    std::cerr << "Błąd: " << msg << "\n";
}

void ConsoleView::printStats(int pawns, const std::chrono::seconds &czas)
{
    std::cout << "\nKONIEC GRY!\n";
    std::cout << "Pozostałe pionki: " << pawns << "\n";
    std::cout << "Czas gry: " << czas.count() / 60 << ":"
              << czas.count() % 60 << "\n";
}

void ConsoleView::showEnd(bool win)
{
    std::cout << (win ? "WYGRANA!" : "PRZEGRANA!") << "\n";
}

ParsedMove GameController::parseInput(const std::string &input) const
{
    if (input.length() != 3)
        throw nieprawidlowe_polecenie();

    const char colChar = toupper(input[0]);
    if (colChar < 'A' || colChar > 'G')
        throw nieprawidlowe_wspolrzedne();
    const int x = colChar - 'A';

    if (!isdigit(input[1]))
        throw nieprawidlowe_polecenie();
    const int y = input[1] - '1';

    const char dirChar = toupper(input[2]);
    Kierunek dir;
    switch (dirChar)
    {
    case 'L':
        dir = Kierunek::LEWO;
        break;
    case 'R':
        dir = Kierunek::PRAWO;
        break;
    case 'U':
        dir = Kierunek::GORA;
        break;
    case 'D':
        dir = Kierunek::DOL;
        break;
    default:
        throw nieprawidlowe_polecenie();
    }

    if (x < 0 || x >= 7 || y < 0 || y >= 7)
        throw nieprawidlowe_wspolrzedne();
    return {x, y, dir};
}

seconds GameController::countGameTime() const
{
    return duration_cast<seconds>(steady_clock::now() - model.getStartTime());
}

void GameController::start()
{
    model = GameModel();
    view.drawBoard(model.getBoard());

    while (!model.isEnd())
    {
        std::cout << "\nPodaj ruch (np. F4L): ";
        std::string input;
        std::cin >> input;

        try
        {
            auto cmd = parseInput(input);

            if (!model.getBoard()[cmd.y][cmd.x])
            {
                throw brak_pionka();
            }

            if (model.isMoveValid(cmd.x, cmd.y, cmd.dir))
            {
                model.move(cmd.x, cmd.y, cmd.dir);
                view.drawBoard(model.getBoard());
            }
            else
            {
                throw nieprawidlowy_ruch();
            }
        }
        catch (const wyjatek_samotnika &e)
        {
            view.printMistake(e.what());
            view.drawBoard(model.getBoard());
        }
    }

    const auto czas = countGameTime();
    view.printStats(model.numOfPawns(), czas);
    view.showEnd(model.numOfPawns() == 1);
}

void GameController::restartGame()
{
    model = GameModel();
    view.drawBoard(model.getBoard()); // Redraw the board
}