#include "samotnik.hpp"
#include <iostream>

int main() {
    GameController controller;
    char choice;

    do {
        controller.start();
        std::cout << "\nCzy chcesz zagrac ponownie? (T/N): ";
        std::cin >> choice;
        std::cin.ignore();
    } while(toupper(choice) == 'T');

    return 0;
}