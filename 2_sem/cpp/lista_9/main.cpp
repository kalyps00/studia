#include "model.hpp"
#include "view.hpp"
#include "controler.hpp"

int main()
{
    Model model;
    View view;
    Controller controller(model, view);

    // Print welcome message
    std::cout << "\n========== PEG SOLITAIRE ==========\n"
              << std::endl;
    std::cout << "Goal: Leave only one peg on the board." << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  - Move format: [Column][Row][Direction]" << std::endl;
    std::cout << "    Example: F4L (Move peg at F4 to the left)" << std::endl;
    std::cout << "  - Directions: L (Left), R (Right), U (Up), D (Down)" << std::endl;
    std::cout << "  - Other commands: q (Quit), r (Restart), s (Surrender)" << std::endl;
    std::cout << "  - Pegs are represented by '●' and empty spaces by '○'" << std::endl;
    std::cout << "  - Press Any Key to Start The Game" << std::endl;
    std::cout << "\n==================================\n"
              << std::endl;

    getchar(); // Wait for user input to start the game
    // Start the game
    controller.run();
}
