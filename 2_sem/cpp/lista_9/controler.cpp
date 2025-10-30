#include "controler.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

Controller::Controller(Model &m, View &v) : model(m), view(v) {}

void Controller::processCommand(const std::string &command)
{
    // Check if command is for quitting or restarting
    if (command == "quit" || command == "q")
    {
        model.set_game_state(QUIT);
        return;
    }
    if (command == "restart" || command == "r")
    {
        model.reset_game();
        return;
    }
    if (command == "surrender" || command == "s")
    {
        model.set_game_state(SURRENDER);
        return;
    }

    // Validate command format (e.g., "F4L")
    if (command.length() != 3)
    {
        throw std::runtime_error("Invalid command format. Use format like 'F4L'");
    }

    // Parse coordinates
    char col = std::toupper(command[0]);
    char row = command[1];
    char direction = std::toupper(command[2]);

    // Validate input ranges
    if (col < 'A' || col > 'G')
    {
        throw std::runtime_error("Column must be between A and G");
    }
    if (row < '1' || row > '7')
    {
        throw std::runtime_error("Row must be between 1 and 7");
    }
    if (direction != 'L' && direction != 'R' && direction != 'U' && direction != 'D')
    {
        throw std::runtime_error("Direction must be L, R, U, or D");
    }

    // Convert to 0-based coordinates
    int x = row - '1';
    int y = col - 'A';

    // Calculate target coordinates based on direction
    int target_x = x;
    int target_y = y;

    switch (direction)
    {
    case 'L':
        target_y -= 2;
        break;
    case 'R':
        target_y += 2;
        break;
    case 'U':
        target_x -= 2;
        break;
    case 'D':
        target_x += 2;
        break;
    }

    // Make the move
    model.make_move(x, y, target_x, target_y);
}

void Controller::run()
{
    std::string command;
    bool running = true;

    while (running)
    {
        // Display current game state
        view.displayBoard(model);

        // Check game state
        switch (model.get_game_state())
        {
        case WIN:
            view.displayMessage("Congratulations! You've won the game!");
            view.displayGameStats(model);
            running = false;
            continue;

        case LOST:
            view.displayMessage("Game over! No more moves available.");
            view.displayGameStats(model);
            running = false;
            continue;

        case SURRENDER:
            view.displayMessage("You surrendered the game.");
            view.displayGameStats(model);
            running = false;
            continue;

        case QUIT:
            view.displayGameStats(model);
            view.displayMessage("Game ended. Goodbye!");
            running = false;
            continue;

        case RESTART:
            view.displayMessage("Game restarted!");
            continue;

        case PLAYING:
            // Continue playing
            break;
        }

        // Get user input
        view.displayPrompt();
        command = view.getUserInput();

        // Convert to lowercase for ease of comparison
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        try
        {
            processCommand(command);
        }
        catch (OutOfBoardException &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        catch (EmptyFieldException &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        catch (OccupiedFieldException &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        catch (NoMiddlePieceException &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        catch (InvalidMoveFormatException &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        catch (std::exception &e)
        {
            view.displayError(e.what());
            std::cout << "Press any key to continue..." << std::endl;
            getchar(); // Wait for user input
        }
        view.clearScreen();
    }
}