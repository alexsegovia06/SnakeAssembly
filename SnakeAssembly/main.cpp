#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
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
    std::string clearLine(BOARD_WIDTH * CELL_WIDTH + 2, ' ');

    while (play) {
        bool running = true;
        int movementDelay = chooseDifficulty();

        initSnake(s, 10, 5, 3);
        placeFood(s);
        resetDirection();
        int score = 0;

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
                std::cout << clearLine;
                continue;
            }

            gotoXY(0, computeBorderLength() - 10);
            std::cout << clearLine;

            s.dir = newDir;

            Position newHead = nextPosition(s.body[0], s.dir);
            bool grow = isHeadOnFood(newHead.x, newHead.y);

            if (!isInsideBoard(newHead.x, newHead.y) || isSnakeCollidingWithItself(s, newHead, grow)) {
                gotoXY(0, BOARD_HEIGHT + 4);
                drawLose();
                std::cout << "    Final Score: " << score << "\n";
                running = false;
                continue;
            }

            Position oldTail = moveSnake(s, newHead, grow);
            if (grow) {
                score = addScore(score, POINTS_PER_FOOD);

                if ((int)s.body.size() == BOARD_WIDTH * BOARD_HEIGHT) {
                    gotoXY(0, BOARD_HEIGHT + 4);
                    drawWin();
                    std::cout << "    Final Score: " << score << "\n";
                    running = false;
                    continue;
                }
                placeFood(s);
            }
            else {
                gotoCell(oldTail.x, oldTail.y);
                std::cout << "  ";
            }

            gotoXY(0, BOARD_HEIGHT + 3);
            std::cout << "Score: " << score << "   ";

            drawSnake(s);
            drawFood();
            gameDelay(movementDelay);
        }
        play = drawWannaPlayAgain();
    }
    return 0;
}