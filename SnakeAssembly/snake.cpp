#include <iostream>
#include "snake.h"
#include "board.h"
#include "input.h"

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

bool isSnakeCollidingWithItself(const Snake& s) {
	Position newHead = nextPosition(s.body[0], s.dir);
	for (size_t i = 1; i + 1 < s.body.size(); i++) {
		if (newHead.x == s.body[i].x && newHead.y == s.body[i].y) {
			return true;
		}
	}
	return false;
}

void drawSnake(const Snake& s) {
	for (size_t i = s.body.size(); i > 1; i--) {
		const Position& segment = s.body[i - 1];
		gotoXY(segment.x+1, segment.y+1);
		std::cout << 0;
	}

	char headChar = '>';
	switch (s.dir) {
		case UP: headChar = '^'; break;
		case DOWN: headChar = 'v'; break;
		case LEFT: headChar = '<'; break;
		case RIGHT: headChar = '>'; break;
	}
	gotoXY(s.body[0].x+1, s.body[0].y+1);
	std::cout << headChar;
}