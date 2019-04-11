#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"
#include <stdlib.h>

#define dec(num) (((num) - 1 > 0) ? (num) - 1 : ARRSIZE - 1)
#define inc(num) (((num) + 1 < ARRSIZE) ? (num) + 1 : 1)

// Note that these have undefined behavior if we use something like a++
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define ARRSIZE 3

#define a appState
#define c currentAppState
#define n nextAppState 
#define handleButton(lefts, lefts_i) \
    int dist = abs(n.lefts[n.lefts_i]); \
    if (dist == 0) { \
        n.message = 1; \
        n.streak++; \
    } else if (dist <= 2) { \
        n.message = 2; \
        n.streak++; \
    } else if (dist <= 8) { \
        n.message = 3; \
        n.streak++; \
    } else if (dist <= 16) { \
        n.message = 4; \
        n.streak = 0; \
    } else if (dist <= 32) { \
        n.message = 5; \
        n.streak = 0; \
    } else { \
        n.message = 6; \
        n.streak = 0; \
    } \
    n.points += (16 - dist) * 2 + n.streak; \
    n.lefts[n.lefts_i] = max(160, n.lefts[dec(n.lefts_i)]) + randint(32, 80); \
    n.lefts_i = inc(n.lefts_i);

typedef struct {
    int x;
    int y;
    int vx;
    int vy;
} Bouncy;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;

    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */
    int ingame; // 0 if we're still on the title screen, 1 otherwise
    Bouncy title;
    int lefts[ARRSIZE];
    int downs[ARRSIZE];
    int As[ARRSIZE];
    int Bs[ARRSIZE];
    int lefts_i; // index of the minimum position in lefts (1 to 9)
    int downs_i;
    int As_i;
    int Bs_i;
    int message; // e.g., awesome! terrible!
    int streak;
    int points;
    int time;
} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
