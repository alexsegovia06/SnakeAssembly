#pragma once
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	INVALID,
	STOP,
	BEGINNING
};

Direction updateDirection();
void resetDirection();