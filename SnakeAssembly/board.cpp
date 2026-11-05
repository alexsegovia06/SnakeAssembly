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

bool isInsideBoard(int x, int y) {
    int result = 0;
    __asm {
        mov eax, x
        cmp eax, 0
        jl out_of_bounds
        cmp eax, BOARD_WIDTH
        jge out_of_bounds
        mov eax, y
        cmp eax, 0
        jl out_of_bounds
        cmp eax, BOARD_HEIGHT
        jge out_of_bounds
        mov result, 1
        jmp bounds_done
        out_of_bounds :
        mov result, 0
            bounds_done :
    }
    return result != 0;
}