#include <stdio.h>
#include "draw.h"
#include "gba.h"
#include "images/arrows.h"

// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
// #include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    for (int i = 0; i < ARRSIZE; i++) {
        drawImageDMA(0, state->lefts[i], 32, 32, left);
        drawImageDMA(32, state->downs[i], 32, 32, down);
        drawImageDMA(64, state->As[i], 32, 32, A);
        drawImageDMA(96, state->Bs[i], 32, 32, B);
    }
    char *messageStr;
    switch (state->message) {
        case 1: messageStr = "YABAI!"; break;
        case 2: messageStr = "SUGOI!"; break;
        case 3: messageStr = "YOSHI!"; break;
        case 4: messageStr = "warui"; break;
        case 5: messageStr = "ganbatte!"; break;
        case 6: messageStr = "hwaiting!"; break;
        default: messageStr = "";
    }
    char streakStr[20];
    snprintf(streakStr, sizeof(streakStr), "%s%d", "Streak: ", state->streak);
    char scoreStr[20];
    snprintf(scoreStr, sizeof(scoreStr), "%s%d", "Score: ", state->points);

    drawString(0, 130, messageStr, WHITE);
    drawString(0, 140, streakStr, WHITE);
    drawString(0, 150, scoreStr, WHITE);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    for (int i = 0; i < ARRSIZE; i++) {
        drawRectDMA(0, state->lefts[i], 32, 32, BLACK);
        drawRectDMA(32, state->downs[i], 32, 32, BLACK);
        drawRectDMA(64, state->As[i], 32, 32, BLACK);
        drawRectDMA(96, state->Bs[i], 32, 32, BLACK);
    }
    drawRectDMA(0, 130, 60, 8, BLACK);
    drawRectDMA(0, 140, 60, 8, BLACK);
    drawRectDMA(0, 150, 90, 8, BLACK); // erase text
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    fullDrawAppState(state);
}
