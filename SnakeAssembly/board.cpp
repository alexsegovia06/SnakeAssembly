#include <iostream>
#include <windows.h>
#include "board.h"

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBoard() {
    for (int x = 0; x < BOARD_WIDTH + 2; x++) std::cout << "#";
    std::cout << "\n";
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        std::cout << "#";
        for (int x = 0; x < BOARD_WIDTH; x++) std::cout << " ";
        std::cout << "#\n";
    }
    for (int x = 0; x < BOARD_WIDTH + 2; x++) std::cout << "#";
    std::cout << "\n";
}

int computeBorderLength() {
    int result = 0;
    __asm {
        mov eax, BOARD_WIDTH
        add eax, 2
        mov result, eax
    }
    return result;
}