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
        mov eax, key          // Copia el codigo de tecla a EAX para compararlo.

        cmp eax, 72           // Compara con el codigo de flecha arriba.
        je key_up             // Salta a key_up si coincide.
        cmp eax, 'w'           // Compara con la letra w minuscula.
        je key_up             // Salta a key_up si coincide.
        cmp eax, 'W'           // Compara con la letra W mayuscula.
        je key_up             // Salta a key_up si coincide.

        cmp eax, 80           // Compara con el codigo de flecha abajo.
        je key_down           // Salta a key_down si coincide.
        cmp eax, 's'           // Compara con la letra s minuscula.
        je key_down           // Salta a key_down si coincide.
        cmp eax, 'S'           // Compara con la letra S mayuscula.
        je key_down           // Salta a key_down si coincide.

        cmp eax, 75           // Compara con el codigo de flecha izquierda.
        je key_left           // Salta a key_left si coincide.
        cmp eax, 'a'           // Compara con la letra a minuscula.
        je key_left           // Salta a key_left si coincide.
        cmp eax, 'A'           // Compara con la letra A mayuscula.
        je key_left           // Salta a key_left si coincide.

        cmp eax, 77           // Compara con el codigo de flecha derecha.
        je key_right          // Salta a key_right si coincide.
        cmp eax, 'd'           // Compara con la letra d minuscula.
        je key_right          // Salta a key_right si coincide.
        cmp eax, 'D'           // Compara con la letra D mayuscula.
        je key_right          // Salta a key_right si coincide.

        cmp eax, 27           // Compara con el codigo de Escape.
        je key_stop           // Salta a key_stop si se presiono Escape.
        jmp key_done          // Si no coincide ninguna tecla, termina con INVALID.

        key_up:               // Etiqueta del caso direccion arriba.
            mov result, UP    // Guarda UP como resultado.
            jmp key_done      // Salta al final para no revisar otros casos.
        key_down:             // Etiqueta del caso direccion abajo.
            mov result, DOWN  // Guarda DOWN como resultado.
            jmp key_done      // Salta al final para no revisar otros casos.
        key_left:             // Etiqueta del caso direccion izquierda.
            mov result, LEFT  // Guarda LEFT como resultado.
            jmp key_done      // Salta al final para no revisar otros casos.
        key_right:            // Etiqueta del caso direccion derecha.
            mov result, RIGHT // Guarda RIGHT como resultado.
            jmp key_done      // Salta al final para no revisar otros casos.
        key_stop:             // Etiqueta del caso tecla Escape.
            mov result, STOP  // Guarda STOP como resultado.

        key_done:             // Punto comun de salida del bloque ASM.
    }
    return static_cast<Direction>(result);
}

bool areOppositeDirections(Direction first, Direction second) {
    int res;

	__asm {
		mov ecx, first          // Guarda en ECX la primera direccion.
		mov edx, second         // Guarda en EDX la segunda direccion.
		mov eax, 0              // Inicializa el resultado: por defecto no son opuestas.

		cmp ecx, UP             // Comprueba si la primera direccion es UP.
		je check_up             // Si es UP, revisa si la segunda es DOWN.
		cmp ecx, DOWN           // Comprueba si la primera direccion es DOWN.
		je check_down           // Si es DOWN, revisa si la segunda es UP.
		cmp ecx, LEFT           // Comprueba si la primera direccion es LEFT.
		je check_left           // Si es LEFT, revisa si la segunda es RIGHT.
		cmp ecx, RIGHT          // Comprueba si la primera direccion es RIGHT.
		je check_right          // Si es RIGHT, revisa si la segunda es LEFT.
		jmp finish_check        // Si no es una direccion valida, conserva el resultado falso.

		check_up:               // Caso: la primera direccion es UP.
			cmp edx, DOWN       // Compara la segunda direccion con DOWN.
			je opposite         // Si coincide, las direcciones son opuestas.
			jmp finish_check   // Si no coincide, termina con falso.

		check_down:             // Caso: la primera direccion es DOWN.
			cmp edx, UP         // Compara la segunda direccion con UP.
			je opposite         // Si coincide, las direcciones son opuestas.
			jmp finish_check   // Si no coincide, termina con falso.

		check_left:             // Caso: la primera direccion es LEFT.
			cmp edx, RIGHT      // Compara la segunda direccion con RIGHT.
			je opposite         // Si coincide, las direcciones son opuestas.
			jmp finish_check   // Si no coincide, termina con falso.

		check_right:            // Caso: la primera direccion es RIGHT.
			cmp edx, LEFT       // Compara la segunda direccion con LEFT.
			je opposite         // Si coincide, las direcciones son opuestas.
			jmp finish_check   // Si no coincide, termina con falso.

		opposite:               // Etiqueta comun para las combinaciones opuestas.
			mov eax, 1          // Marca el resultado como verdadero.

		finish_check:           // Punto comun para guardar el resultado.
			mov res, eax        // Copia el resultado ASM a la variable C++ res.
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