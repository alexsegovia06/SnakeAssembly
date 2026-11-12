#include <iostream>

void drawWin() {
	std::cout << "\n    You Win!\n";
}

void drawLose() {
	std::cout << "\n    You Lose!\n";
}

void drawBeginningMessage() {
	std::cout << "Press a direction key to start the game...\n";
}

bool drawWannaPlayAgain() {
	std::cout << "\nDo you want to play again? (Y/N): ";
	char choice;
	std::cin >> choice;
	return (choice == 'Y' || choice == 'y');
}