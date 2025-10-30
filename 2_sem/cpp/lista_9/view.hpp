#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <string>
#include "model.hpp"

class View
{
public:
    void displayBoard(const Model &model);
    std::string getUserInput();
    void displayMessage(const std::string &message);
    void displayPrompt();
    void displayError(const std::string &message);
    void displayGameStats(const Model &model);
    void clearScreen();
};

#endif // VIEW_HPP
