#pragma once
#include <vector>
#include "input.h"

struct Position {
    int x; //columna
    int y; // fila
};

// Representa la serpiente en el juego
struct Snake {
	std::vector<Position> body;
	Direction dir;
};

// Constantes para el puntaje y la longitud máxima de la serpiente
const int POINTS_PER_FOOD = 10;
const int MAX_LENGTH = 100;
extern Position snakeBody [MAX_LENGTH];
extern int snakeLength;

// Funciones para manejar la serpiente
void initSnake(Snake& s, int x, int y, int length);
void printSnake(const Snake& s);

// Calcula dónde quedará la cabeza en el siguiente movimiento
Position nextPosition(Position head, Direction dir);             
Position moveSnake(Snake& s, Position newHead, bool grow);
bool isSnakeCollidingWithItself(const Snake& s, Position newHead, bool grow);
int addScore(int score, int points);                             
void drawSnake(const Snake& s);