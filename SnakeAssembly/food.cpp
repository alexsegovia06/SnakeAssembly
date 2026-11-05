#include <iostream>
#include "food.h"
#include "board.h"

Position food;

void initFood() {
    food = { 10, 5 };
}

void drawFood() {
    gotoXY(food.x + 1, food.y + 1);
    std::cout << "*";
}