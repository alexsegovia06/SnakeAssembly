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

## Architecture

| Tool | What it's for |
|---|---|
| Visual Studio | IDE used to write, build and run the project |
| x86 Assembler (inline `__asm`) | Low-level language used for the core game-logic decisions (movement, collisions, scoring, random food) |
| C++ | Orchestrates the program: console I/O, the main loop, and the data structures that hold the game state |

Calling convention: `cdecl`. No external assembler/linker or simulator — the game runs natively in the Windows console.

## Features implemented so far

- Full board rendered as the game's background, scaled to 2-character-wide cells so it reads better in a console font (characters are taller than they are wide).
- Snake drawn on top of the board with color (body in green, head in cyan, changes glyph per direction).
- Non-blocking keyboard input (arrow keys or WASD), with 180° turn prevention done in assembly.
- Real movement: the next head position is computed in assembly (`nextPosition`), and the body follows it every frame.
- Random food placement (`asmMod`, assembly) that never lands on top of the snake (`isFoodOnSnake`, assembly).
- Eating detection (`isHeadOnFood`, assembly): the snake grows by one segment and new food is placed elsewhere.
- Border collision (`isInsideBoard`, assembly) and self-collision (`isSnakeCollidingWithItself`) both end the game.
- Score counter, incremented in assembly (`addScore`) and shown on screen.
- Difficulty selector (easy / medium / hard) that changes the game's speed.
- Win condition (snake fills the whole board) and lose condition (collision), each with its own end screen and final score.
- "Play again?" prompt after each game ends.

## How to build and run

1. Open the solution in Visual Studio.
2. Make sure the active platform is set to **x86** (not x64) — required for inline assembly.
3. Build the solution (`Build → Rebuild Solution` if you changed code and it doesn't seem to take effect).
4. Run it (`Local Windows Debugger` / F5).

## Controls

- Arrow keys or **W A S D** to move.
- **ESC** to quit.
- At the start of each game, choose a difficulty (1 = Easy, 2 = Medium, 3 = Hard).
- After losing or winning, choose whether to play again (Y/N).

## Status

- [x] Board rendering
- [x] Snake rendering
- [x] Real movement (keyboard-controlled)
- [x] Random food placement
- [x] Growth on eating
- [x] Border collision
- [x] Self-collision
- [x] Scoring
- [x] Difficulty levels
- [x] Win / lose screens
- [ ] Final polish and presentation rehearsal
