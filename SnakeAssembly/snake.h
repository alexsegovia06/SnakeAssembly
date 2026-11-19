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

const int POINTS_PER_FOOD = 10;

void initSnake(Snake& s, int x, int y, int length);
void printSnake(const Snake& s);
Position nextPosition(Position head, Direction dir);             
Position moveSnake(Snake& s, Position newHead, bool grow);
bool isSnakeCollidingWithItself(const Snake& s, Position newHead, bool grow);
int addScore(int score, int points);                             
void drawSnake(const Snake& s);