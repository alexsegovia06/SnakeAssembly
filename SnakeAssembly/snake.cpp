#include <iostream>
#include "snake.h"
#include "board.h"

Position snakeBody[MAX_LENGTH];
int snakeLength;

void initSnake(Snake& s, int x, int y, int length) {
	s.body.clear();
    for (int i = 0; i < length; i++) {
        Position next = {x - i, y};
        s.body.push_back(next);
    }
	s.dir = RIGHT;
}

void printSnake(const Snake& s) {
    for (size_t i = 0; i < s.body.size(); i++) {
		std::cout << "Segmento " << i << ": (" << s.body[i].x << ", " << s.body[i].y << ")\n";
    }
}

Position nextPosition(Position head, Direction dir) {
	int movX = 0, movY = 0;
	switch (dir) {
	case UP:
		movY = -1;
		break;
	case DOWN:
		movY = 1;
		break;
	case LEFT:
		movX = -1;
		break;
	case RIGHT:
		movX = 1;
		break;
	}

	int x = head.x;
	int y = head.y;

	__asm {
		mov eax, x; eax = x actual de la cabeza
		add eax, movX; eax = x + movX
		mov x, eax; guardar la nueva x

		mov eax, y; eax = y actual de la cabeza
		add eax, movY; eax = y + movY
		mov y, eax; guardar la nueva y
	}

	Position next = { x, y };
	return next;
}