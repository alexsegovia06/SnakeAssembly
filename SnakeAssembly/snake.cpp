#include <iostream>
#include "snake.h"
#include "board.h"
#include "input.h"


void initSnake(Snake& s, int x, int y, int length) {
	s.body.clear();
	for (int i = 0; i < length; i++) {
		Position next = { x - i, y };
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
		mov eax, x
		add eax, movX
		mov x, eax

		mov eax, y
		add eax, movY
		mov y, eax
	}

	Position next = { x, y };
	return next;
}

bool isSnakeCollidingWithItself(const Snake& s, Position newHead, bool grow) {
	size_t limit = s.body.size();
	if (!grow) limit--;
	for (size_t i = 1; i < limit; i++) {
		if (newHead.x == s.body[i].x && newHead.y == s.body[i].y) {
			return true;
		}
	}
	return false;
}

void drawSnake(const Snake& s) {
	setColor(COLOR_SNAKE_BODY);
	for (size_t i = s.body.size(); i > 1; i--) {
		const Position& segment = s.body[i - 1];
		const Position& towardsHead = s.body[i - 2];
		gotoCell(segment.x, segment.y);
		if (segment.y == towardsHead.y) {
			std::cout << "OO";
		}
		else {
			std::cout << "O ";
		}
	}

	setColor(COLOR_SNAKE_HEAD);
	const char* headGlyph = ">>";
	switch (s.dir) {
	case UP:    headGlyph = "^ "; break;
	case DOWN:  headGlyph = "v "; break;
	case LEFT:  headGlyph = "<0"; break;
	case RIGHT: headGlyph = "0>"; break;
	}
	gotoCell(s.body[0].x, s.body[0].y);
	std::cout << headGlyph;

	setColor(COLOR_DEFAULT);
}

int addScore(int score, int points) {
	int result = score;
	__asm {
		mov eax, result
		add eax, points
		mov result, eax
	}
	return result;
}

Position moveSnake(Snake& s, Position newHead, bool grow) {
	Position oldTail = s.body.back();
	if (grow) {
		s.body.insert(s.body.begin(), newHead);
	}
	else {
		for (size_t i = s.body.size() - 1; i > 0; i--) {
			s.body[i] = s.body[i - 1];
		}
		s.body[0] = newHead;
	}
	return oldTail;
}