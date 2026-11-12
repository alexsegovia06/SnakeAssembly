#pragma once
#include <vector>
#include "input.h"

struct Position {
    int x; //columna
    int y; // fila
};

struct Snake {
	std::vector<Position> body;
	Direction dir;
};

const int MAX_LENGTH = 100;
extern Position snakeBody[MAX_LENGTH];
extern int snakeLength;

void initSnake(Snake& s, int x, int y, int length);
void printSnake(const Snake& s);
Position nextPosition(Position head, Direction dir);

void initSnake();
void drawSnake(const Snake& s);
void debugPrintSnake();
bool isSnakeCollidingWithItself(const Snake& s);