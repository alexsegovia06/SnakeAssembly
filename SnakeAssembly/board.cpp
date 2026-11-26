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
        mov eax, x              // carga la coordenada x en EAX
        cmp eax, 0              // compara x con 0 (límite izquierdo)
        jl out_of_bounds        // si x < 0, está fuera del tablero
        cmp eax, BOARD_WIDTH    // compara x con el ancho del tablero
        jge out_of_bounds       // si x >= BOARD_WIDTH, está fuera (columnas válidas: 0..BOARD_WIDTH-1)
        mov eax, y              // carga la coordenada y en EAX
        cmp eax, 0              // compara y con 0 (límite superior)
        jl out_of_bounds        // si y < 0, está fuera del tablero
        cmp eax, BOARD_HEIGHT   // compara y con el alto del tablero
        jge out_of_bounds       // si y >= BOARD_HEIGHT, está fuera (filas válidas: 0..BOARD_HEIGHT-1)
        mov result, 1           // pasó las 4 comparaciones: la posición es válida
        jmp bounds_done         // evita caer en la rama de "fuera de rango"
    out_of_bounds:
        mov result, 0           // marca la posición como inválida
    bounds_done:
    }
    return result != 0;
}