#include <conio.h>
#include "input.h"

Direction lastDirection = BEGINNING;
Direction newDirection = BEGINNING;

bool keyAvailable() {
    return _kbhit() != 0;
}

int readKey() {
    return _getch();
}

Direction keyValid() {
    if (!_kbhit()) return INVALID;

    int key = _getch();

    // Las flechas llegan como un prefijo y luego su código
    if (key == 0 || key == 224) {
        key = _getch();
    }

    int result = INVALID;

    __asm {
        mov eax, key

        cmp eax, 72       // Flecha arriba
        je key_up
        cmp eax, 'w'
        je key_up
        cmp eax, 'W'
        je key_up

        cmp eax, 80       // Flecha abajo
        je key_down
        cmp eax, 's'
        je key_down
        cmp eax, 'S'
        je key_down

        cmp eax, 75       // Flecha izquierda
        je key_left
        cmp eax, 'a'
        je key_left
        cmp eax, 'A'
        je key_left

        cmp eax, 77       // Flecha derecha
        je key_right
        cmp eax, 'd'
        je key_right
        cmp eax, 'D'
        je key_right

        cmp eax, 27       // Escape
        je key_stop
        jmp key_done

        key_up :
            mov result, UP
            jmp key_done
        key_down :
            mov result, DOWN
            jmp key_done
        key_left :
            mov result, LEFT
            jmp key_done
        key_right :
            mov result, RIGHT
            jmp key_done
        key_stop :
        mov result, STOP

        key_done :
    }
    return static_cast<Direction>(result);
}

bool areOppositeDirections(Direction first, Direction second) {
    int res;

    __asm {
        mov ecx, first
        mov edx, second
		mov eax, 0

		cmp ecx, UP
        je check_up
        cmp ecx, DOWN
        je check_down
        cmp ecx, LEFT
        je check_left
        cmp ecx, RIGHT
        je check_right
        jmp finish_check

        check_up :
            cmp edx, DOWN
            je opposite
            jmp finish_check

        check_down :
            cmp edx, UP
            je opposite
            jmp finish_check

        check_left :
            cmp edx, RIGHT
            je opposite
            jmp finish_check

        check_right :
            cmp edx, LEFT
            je opposite
            jmp finish_check

        opposite :
            mov eax, 1

        finish_check :
            mov res, eax
    }

    return res != 0;
}

Direction updateDirection() {
	Direction newDir = keyValid();
    if (newDir != INVALID && !areOppositeDirections(lastDirection, newDir)) {
        newDirection = newDir;
        lastDirection = newDir;
    }
	return  newDirection;
}

void resetDirection() {
	lastDirection = BEGINNING;
	newDirection = BEGINNING;
}