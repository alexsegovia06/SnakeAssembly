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
        mov eax, value          // carga el dividendo en EAX
        cdq                     // extiende el signo de EAX a EDX:EAX (lo exige idiv con signo)
        idiv divisor            // divide EDX:EAX entre divisor; EAX = cociente, EDX = residuo
        mov result, edx         // el residuo (EDX) es lo que da el módulo
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
        mov esi, arr            // ESI guarda la dirección base del arreglo de segmentos
        mov ecx, 0              // ECX funciona como índice i, empieza en 0
    check_loop:
        cmp ecx, len            // compara i con el número de segmentos
        jge check_done          // si i >= len, ya se revisó todo el cuerpo
        mov eax, ecx            // copia i a EAX para calcular el offset
        imul eax, 8             // cada Position mide 8 bytes (x e y, 4 bytes cada uno)
        add eax, esi            // EAX = dirección del segmento i (base + offset)
        mov edx, [eax]          // EDX = segmento[i].x
        cmp edx, fx             // compara x del segmento con la x de la comida
        jne next_i              // si son distintos, no es este segmento
        mov edx, [eax + 4]      // EDX = segmento[i].y
        cmp edx, fy             // compara y del segmento con la y de la comida
        jne next_i              // si son distintos, no es este segmento
        mov found, 1            // x e y coinciden: la comida cayó sobre el cuerpo
        jmp check_done          // ya se encontró, no hace falta seguir
    next_i:
        inc ecx                 // i++
        jmp check_loop          // repite con el siguiente segmento
    check_done:
    }
    return found != 0;
}

void placeFood(const Snake& s) {
    do {
        food.x = asmMod(rand(), BOARD_WIDTH);   // aleatorio % ancho -> columna válida (0..BOARD_WIDTH-1)
        food.y = asmMod(rand(), BOARD_HEIGHT);  // aleatorio % alto -> fila válida (0..BOARD_HEIGHT-1)
    } while (isFoodOnSnake(s));                  // si cae sobre el cuerpo, se vuelve a sortear
}

bool isHeadOnFood(int headX, int headY) {
    int result;
    __asm {
        mov eax, headX          // carga la x de la cabeza en EAX
        cmp eax, food.x         // compara con la x de la comida
        jne not_equal           // si son distintas, no hay coincidencia
        mov eax, headY          // carga la y de la cabeza en EAX
        cmp eax, food.y         // compara con la y de la comida
        jne not_equal           // si son distintas, no hay coincidencia
        mov result, 1           // x e y coinciden: la cabeza está sobre la comida
        jmp eq_done             // evita caer en la rama de "no coincide"
        not_equal :
        mov result, 0           // marca que la cabeza no está sobre la comida
            eq_done :
    }
    return result != 0;
}

void drawFood() {
    gotoCell(food.x, food.y);
    setColor(COLOR_FOOD);
    std::cout << "* ";
    setColor(COLOR_DEFAULT);
}