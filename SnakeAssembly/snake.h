#pragma once
#include <vector>

struct Position {
    int x; //columna
    int y; // fila
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
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
void drawSnake();
void debugPrintSnake();