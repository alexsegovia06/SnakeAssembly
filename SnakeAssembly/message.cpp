#include <iostream>
#include <string>
#include <cstdlib> 
#include <conio.h>
#include <fstream>
#include "board.h"

static void drawFramedMessage(const std::string& text, int color) {
    const char* borderChar = "\xB2";
    int innerWidth = (int)text.size() + 4; // 2 espacios de margen a cada lado
    int pad = 2;

    setColor(color);
    for (int i = 0; i < innerWidth + 2; i++) std::cout << borderChar;
    std::cout << "\n";

    std::cout << borderChar;
    setColor(COLOR_DEFAULT);
    for (int i = 0; i < pad; i++) std::cout << " ";
    std::cout << text;
    for (int i = 0; i < pad; i++) std::cout << " ";
    setColor(color);
    std::cout << borderChar << "\n";

    for (int i = 0; i < innerWidth + 2; i++) std::cout << borderChar;
    std::cout << "\n";

    setColor(COLOR_DEFAULT);
}

void drawWin() {
    drawFramedMessage("You Win!", COLOR_SUCCESS);
}

void drawLose() {
    drawFramedMessage("You Lose!", COLOR_DANGER);
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

void drawTitleScreen() {
    system("cls");
    setColor(COLOR_SUCCESS);
    std::cout
        << "   _____ _   _          _  ________ \n"
        << "  / ____| \\ | |   /\\   | |/ /  ____|\n"
        << " | (___ |  \\| |  /  \\  | ' /| |__   \n"
        << "  \\___ \\| . ` | / /\\ \\ |  < |  __|  \n"
        << "  ____) | |\\  |/ ____ \\| . \\| |____ \n"
        << " |_____/|_| \\_/_/    \\_\\_|\\_\\______|\n";
    setColor(COLOR_DEFAULT);
    std::cout << "\n  Controls:\n"
        << "    Arrows or WASD to move\n"
        << "    ESC to exit\n\n"
        << "  Press any key to continue...";
    _getch();
    system("cls");
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
        return 150;
    }
    if (choice == 2) {
        return 100;
    }
    return 50;
}

int loadHighScore() {
    std::ifstream file("highscore.txt");
    int highScore = 0;
    if (file) {
        file >> highScore;
    }
    return highScore;
}

void saveHighScore(int score) {
    std::ofstream file("highscore.txt");
    file << score;
}