#include "view.hpp"
#include <iostream>
#include <iomanip>
#include <string>

void View::displayBoard(const Model &model)
{
    // clearScreen();
    std::cout << "\n    A B C D E F G" << std::endl;
    std::cout << "  ┌───────────────┐" << std::endl;

    for (int i = 0; i < 7; ++i)
    {
        std::cout << i + 1 << " │";
        for (int j = 0; j < 7; ++j)
        {
            try
            {
                int val = model.get_board_val(i, j);
                if (val == 1)
                { // PEG
                    std::cout << " ●";
                }
                else if (val == 0)
                { // EMPTY
                    std::cout << " ○";
                }
                else
                { // INVALID
                    std::cout << "  ";
                }
            }
            catch (const OutOfBoardException &)
            {
                std::cout << "  ";
            }
        }
        std::cout << " │" << std::endl;
    }

    std::cout << "  └───────────────┘" << std::endl;
    std::cout << "Pegs remaining: " << model.get_peg_count() << std::endl;
}

std::string View::getUserInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void View::displayPrompt()
{
    std::cout << "\nEnter your move (e.g. F4L) or command (q=quit, r=restart, s=surrender): ";
}

void View::displayMessage(const std::string &message)
{
    std::cout << "\n"
              << message << std::endl;
}

void View::displayError(const std::string &error)
{
    std::cout << "\nERROR: " << error << std::endl;
}
void View::clearScreen()
{
    // ANSI escape sequence to clear screen and move cursor to home position
    system("clear");
}
void View::displayGameStats(const Model &model)
{
    double time = model.get_game_time();
    int pegs = model.get_peg_count();

    std::cout << "\n----- Game Statistics -----" << std::endl;
    std::cout << "Time played: " << std::fixed << std::setprecision(1) << time << " seconds" << std::endl;
    std::cout << "Pegs remaining: " << pegs << std::endl;

    // Calculate score (fewer pegs = better score)
    if (pegs == 1)
    {
        std::cout << "Score: Perfect! You won!" << std::endl;
    }
    else
    {
        std::cout << "Score: " << (32 - pegs) << " points (higher is better)" << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
}