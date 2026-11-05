#pragma once

struct Position {
    int x;
    int y;
};

const int MAX_LENGTH = 100;
extern Position snakeBody[MAX_LENGTH];
extern int snakeLength;

void initSnake();
void drawSnake();
void debugPrintSnake();