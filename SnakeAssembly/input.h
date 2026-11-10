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

bool keyAvailable();
Direction keyValid();
char readKey();
bool areOppositeDirections(Direction first, Direction second);
Direction updateDirection();