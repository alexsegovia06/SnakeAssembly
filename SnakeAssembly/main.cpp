//haciendo pruebas de funcionamiento
#include <iostream>

int main() {
    int result = 0;
    __asm {
        mov eax, 6
        add eax, 7
        mov result, eax
    }
    std::cout << "Resultado del test ASM (6+7): " << result << std::endl;
    return 0;
}