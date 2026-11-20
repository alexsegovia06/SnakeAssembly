#pragma once
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 10;

const int CELL_WIDTH = 2;

const int COLOR_DEFAULT = 7;
const int COLOR_BORDER = 8;
const int COLOR_SNAKE_BODY = 10;
const int COLOR_SNAKE_HEAD = 11;
const int COLOR_FOOD = 12;

const int COLOR_SUCCESS = 10;
const int COLOR_DANGER = 12;

void gotoXY(int x, int y);

void gotoCell(int x, int y);

void setColor(int color);

void drawBoard();

int computeBorderLength();

bool isInsideBoard(int x, int y);