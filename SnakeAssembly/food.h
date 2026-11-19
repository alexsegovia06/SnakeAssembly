#pragma once
#include "snake.h"
 
extern Position food;
 
void initFood();                 
void placeFood(const Snake& s); 
void drawFood();
 
bool isHeadOnFood(int headX, int headY);
 
bool isFoodOnSnake(const Snake& s);
 