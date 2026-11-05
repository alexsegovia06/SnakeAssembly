#include <conio.h>
#include "input.h"

bool keyAvailable() {
    return _kbhit() != 0;
}

char readKey() {
    return _getch();
}