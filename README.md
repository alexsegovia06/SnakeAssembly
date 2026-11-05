# Snake - Final Project for Operating Systems Fundamentals & Computer Organization
**Team**: Los Más Capitos
**Members**: Valeria Perez Ochoa, Luis Ángel Robles Rubio and Alejandro Segovia Sarmiento.

## Description
Snake is a video game in which the player controls a snake that moves across a board, grows by eating food, and loses when it hits the edges of the board or its own body.

Unlike a simple sequential input/output program, Snake requires the system to react to two event sources at the same time: the player's keyboard and a timer that advances the game at regular intervals. Because of this, the project focuses on interrupts, real-time control, and the management of a dynamic data structure (the snake's body) represented directly in memory.

## Requirements
- Visual Studio
- Build platform: **x86 (32-bit)**

## Project structure

| File | Module | Owner |
|---|---|---|
| `main.cpp` | Main game loop (integration) | Whole team |
| `board.h` / `board.cpp` | Render: board drawing and console utilities | Render |
| `snake.h` / `snake.cpp` | Game Engine: snake data structure and drawing | Game Engine |
| `input.h` / `input.cpp` | Input/Timer: keyboard reading | Input/Timer |
