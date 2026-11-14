#include <iostream>

void drawWin() {
    std::cout << "\n    You Win!\n";
}

void drawLose() {
    std::cout << "\n    You Lose!\n";
}

void drawBeginningMessage() {
    std::cout << "Press a direction key to start the game...\n";
}

bool drawWannaPlayAgain() {
    std::cout << "\nDo you want to play again? (Y/N): ";
    char choice;
    std::cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int chooseDifficulty() {
    int choice;

    do {
        std::cout << "Choose a difficulty:\n"
            << "1. Easy\n"
            << "2. Medium\n"
            << "3. Hard\n"
            << "Selection: ";
        std::cin >> choice;
    } while (choice < 1 || choice > 3);

    if (choice == 1) {
        return 225;
    }
    if (choice == 2) {
        return 175;
    }
    return 125;
}