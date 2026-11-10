#include <conio.h>
#include "input.h"

bool keyAvailable() {
    return _kbhit() != 0;
}

char readKey() {
    return _getch();
}

Direction keyValid() {
	if (keyAvailable()) {
		int key = readKey();
		if (key == 0 || key == 224) {
			key = readKey();
			switch (key) {
				case 72: return UP;// Up arrow
				case 119: return UP; // 'w' key
				case 80: return DOWN; // Down arrow
				case 115: return DOWN; // 's' key
				case 75: return LEFT; // Left arrow
				case 97: return LEFT; // 'a' key
				case 77: return RIGHT; // Right arrow
				case 100: return RIGHT; // 'd' key
				case 27: return STOP; // Escape key
				default: return INVALID;
			}
		}
	}
	return INVALID;
}

bool areOppositeDirections(Direction first, Direction second) {
    int res;

	// If res = 1, the directions are opposite; if res = 0, they are not opposite
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

		// Check if the second direction is the opposite of the first
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

    if (res == 0) {
        return false;
    }

    return true;
}

void updateDirection() {
    Direction newDir = keyValid();
    if (newDir != INVALID && !areOppositeDirections(lastDirection, newDir)) {
        newDirection = newDir;
        lastDirection = newDir;
    }
}