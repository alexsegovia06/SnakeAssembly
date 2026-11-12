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
	if (keyAvailable()) {
		int key = readKey();
		if (key == 0 || key == 224) {
			key = readKey();
			switch (key) {
				case 72: return UP;// Up arrow
				case 80: return DOWN; // Down arrow
				case 75: return LEFT; // Left arrow
				case 77: return RIGHT; // Right arrow
			}
        }
        else {
            switch (key) {
			case 'w':
			case 'W':
				return UP;
			case 's':
			case 'S':
				return DOWN;
			case 'a':
			case 'A':
				return LEFT;
			case 'd':
			case 'D':
				return RIGHT;
            case 27: return STOP; // Escape key
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