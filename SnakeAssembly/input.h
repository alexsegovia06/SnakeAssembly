#pragma once
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	INVALID,
	STOP
};

Direction lastDirection = RIGHT;
Direction newDirection = RIGHT;

bool keyAvailable();
Direction keyValid();
char readKey();
bool areOppositeDirections(Direction first, Direction second);
void updateDirection();