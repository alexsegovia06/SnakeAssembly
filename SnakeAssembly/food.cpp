#include <iostream>
#include <cstdlib>
#include "food.h"
#include "board.h"

Position food;

void initFood() {
    food = { 10, 5 };
}

int asmMod(int value, int divisor) {
    int result;
    __asm {
        mov eax, value
        cdq
        idiv divisor; edx = residuo
        mov result, edx
    }
    return result;
}

bool isFoodOnSnake(const Snake& s) {
    int len = (int)s.body.size();
    const Position* arr = s.body.data();
    int fx = food.x;
    int fy = food.y;
    int found = 0;
    __asm {
        mov esi, arr
        mov ecx, 0
        check_loop:
        cmp ecx, len
            jge check_done
            mov eax, ecx
            imul eax, 8; Position = 8 bytes(x, y)
            add eax, esi; eax ->& arr[i]
            mov edx, [eax]; x del segmento
            cmp edx, fx
            jne next_i
            mov edx, [eax + 4]; y del segmento
            cmp edx, fy
            jne next_i
            mov found, 1
            jmp check_done
            next_i :
        inc ecx
            jmp check_loop
            check_done :
    }
    return found != 0;
}

void placeFood(const Snake& s) {
    do {
        food.x = asmMod(rand(), BOARD_WIDTH);
        food.y = asmMod(rand(), BOARD_HEIGHT);
    } while (isFoodOnSnake(s));
}

bool isHeadOnFood(int headX, int headY) {
    int result;
    __asm {
        mov eax, headX
        cmp eax, food.x
        jne not_equal
        mov eax, headY
        cmp eax, food.y
        jne not_equal
        mov result, 1
        jmp eq_done
        not_equal :
        mov result, 0
            eq_done :
    }
    return result != 0;
}

void drawFood() {
    gotoXY(food.x + 1, food.y + 1);
    std::cout << "*";
}