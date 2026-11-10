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

	std::cout << "Snake inicializado:\n";
	printSnake(s);

	Position p = nextPosition(s.body[0], s.dir);
	std::cout << "Next position: (" << p.x << ", " << p.y << ") esperando (10+1,5)= (11,5) \n";

	p = nextPosition(s.body[0], UP);
	std::cout << "Next position: (" << p.x << ", " << p.y << ") esperando (10,4) \n";

    std::cout << "\nPresiona Enter para continuar...";
    std::cin.get();

    bool running = true;
    while (running) {
        system("cls");
        //drawBoard();
        //drawSnake();
        drawFood();

        if (keyAvailable()) {
            char key = readKey();
            gotoXY(0, BOARD_HEIGHT + 3);
            std::cout << "Tecla detectada: " << key << "   ";
            if (key == 27) running = false;
        }

        gameDelay(200);
    }

    return 0;
}