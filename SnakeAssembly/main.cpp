// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "snake.h"
#include "food.h"
#include "input.h"
#include "timer.h"
#include "message.h"

int main() {
    srand((unsigned)time(0));
    Snake s;

    bool play = true;

    while (play) {
        bool running = true;

        initSnake(s, 10, 5, 3);
        placeFood(s);
        resetDirection();

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
                    gotoXY(0, computeBorderLength() - 10);
                    std::cout << "                                          ";
                    continue;
                }

                gotoXY(0, computeBorderLength() - 10);
                std::cout << "                                          ";

                s.dir = newDir;

                Position newHead = nextPosition(s.body[0], s.dir);

                if (isSnakeCollidingWithItself(s) || !isInsideBoard(newHead.x, newHead.y)) {
                    drawLose();
                    newDir = STOP;
                    running = false;
                    continue;
                }

                if (isHeadOnFood(newHead.x, newHead.y)) {
                    s.body.insert(s.body.begin(), newHead);
                    placeFood(s);
                }
                else {
                    Position oldTail = s.body.back();

                    for (size_t i = s.body.size() - 1; i > 0; i--) {
                        s.body[i] = s.body[i - 1];
                    }
                    s.body[0] = newHead;

                    gotoXY(oldTail.x + 1, oldTail.y + 1);
                    std::cout << ' ';
                }

                drawSnake(s);
                drawFood();
                gameDelay(150);
            }
        play = drawWannaPlayAgain();
    }
    return 0;
}