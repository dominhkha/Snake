#ifndef CONSTANTS_H
#define CONSTANTS_H

//Mac
#include <SDL2/SDL.h>
// //Windows
// #include <SDL.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Snake Game";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 30;

const SDL_Color BOARD_COLOR = {0, 0, 0};
const SDL_Color LINE_COLOR = {128, 128, 128};

const double STEP_DELAY = 0.2;

#endif 