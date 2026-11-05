#include <iostream>
#include "snake.h"
#include "board.h"

Position snakeBody[MAX_LENGTH];
int snakeLength;

void initSnake() {
    snakeLength = 3;
    snakeBody[0] = { 5, 5 };
    snakeBody[1] = { 4, 5 };
    snakeBody[2] = { 3, 5 };
}

void drawSnake() {
    for (int i = 0; i < snakeLength; i++) {
        gotoXY(snakeBody[i].x + 1, snakeBody[i].y + 1);
        std::cout << "O";
    }
}

void debugPrintSnake() {
    for (int i = 0; i < snakeLength; i++) {
        std::cout << "Segmento " << i << ": (" << snakeBody[i].x << ", " << snakeBody[i].y << ")\n";
    }
}