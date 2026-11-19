#include <iostream>
#include <windows.h>
#include "board.h"

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoCell(int x, int y) {
    gotoXY(x * CELL_WIDTH + 1, y + 1);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void drawBoard() {
    int topLen = BOARD_WIDTH * CELL_WIDTH + 2;

    setColor(COLOR_BORDER);
    for (int x = 0; x < topLen - 1; x++) std::cout << (x % 2 == 0 ? "#" : " ");
    std::cout << "#\n";

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        setColor(COLOR_BORDER);
        std::cout << "#";
        setColor(COLOR_DEFAULT);
        for (int x = 0; x < BOARD_WIDTH * CELL_WIDTH; x++) std::cout << " ";
        setColor(COLOR_BORDER);
        std::cout << "#\n";
    }

    for (int x = 0; x < topLen - 1; x++) std::cout << (x % 2 == 0 ? "#" : " ");
    std::cout << "#\n";

    setColor(COLOR_DEFAULT);
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