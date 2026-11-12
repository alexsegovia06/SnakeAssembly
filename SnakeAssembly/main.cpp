// main.cpp
#include <iostream>
#include "board.h"
#include "snake.h"
#include "food.h"
#include "input.h"
#include "timer.h"

int main() {
    initFood();
    
    Snake s;
	initSnake( s, 10, 5, 3);

    bool running = true;
	Direction newDir = BEGINNING;
	std::cout << "Presiona una tecla de dirección para iniciar el juego...\n";
	system("cls");
	drawBoard();
	drawSnake(s);
    while (running) {
		newDir = updateDirection();
        
		if (newDir == BEGINNING) {
			gameDelay(50);
			continue;
        }

        if (newDir == STOP) {
			running = false;
            continue;
        }

		s.dir = newDir;

		Position newHead = nextPosition(s.body[0], s.dir);

		if (isSnakeCollidingWithItself(s) || !isInsideBoard(newHead.x, newHead.y)) {
			std::cout << "Game Over!\n";
			newDir = STOP;
			running = false;
			continue;
		}

		Position oldTail = s.body.back();

        for (size_t i = s.body.size() - 1; i > 0; i--) {
			s.body[i] = s.body[i - 1];
        }
        s.body[0] = newHead;

		gotoXY(oldTail.x + 1, oldTail.y + 1);
		std::cout << ' ';

		drawSnake(s);
		drawFood();
        gameDelay(150);
    }

    return 0;
}