// main.cpp
#include <iostream>
#include "board.h"
#include "snake.h"
#include "food.h"
#include "input.h"
#include "timer.h"

int main() {
    initSnake();
    initFood();

    bool running = true;
    while (running) {
        system("cls");
        drawBoard();
        drawSnake();
        drawFood();

        if (keyAvailable()) {
            char key = readKey();
            gotoXY(0, BOARD_HEIGHT + 3);
            std::cout << "Tecla detectada: " << key << "   ";
            if (key == 27) running = false;
        }

        gameDelay(200);
    }

    return 0;
}