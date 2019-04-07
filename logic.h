#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

#define dec(num) (((num) - 1 >= 0) ? (num) - 1 : 8) // 8 is the last index of our lefts array
#define inc(num) (((num) + 1 <= 8) ? (num) + 1 : 0)
// Note that this is undefined if we use something like a++
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) >= 0 ? (a) : (-a))

#define a appState
#define n nextAppState
#define handleButton(lefts, lefts_i) \
    int dist = n.lefts[n.lefts_i]; \
    if (dist == 0) { \
        n.message = 1; \
        n.streak++; \
    } else if (dist <= 4) { \
        n.message = 2; \
        n.streak++; \
    } else if (dist <= 8) { \
        n.message = 3; \
    } else if (dist <= 16) { \
        n.message = 4; \
    } else if (dist <= 32) { \
        n.message = 5; \
    } else { \
        n.message = 6; \
    } \
    n.points += (16 - abs(dist)) * 2; \
    n.lefts[n.lefts_i] = min(160, n.lefts[dec(n.lefts_i)]) + randint(0, 50); \
    n.lefts_i = inc(n.lefts_i);

extern volatile OamEntry shadow[128];
extern volatile OamEntry *left;
extern volatile OamEntry *down;
extern volatile OamEntry *up;
extern volatile OamEntry *right;
extern volatile OamEntry *A;
extern volatile OamEntry *B;

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
    /*
    List *lefts;
    List *downs;
    List *ups;
    List *rights;
    List *As;
    List *Bs;*/
    int lefts[9];
    int downs[9];
    int ups[9];
    int rights[9];
    int As[9];
    int Bs[9];
    int lefts_i; // index of the minimum position in lefts
    int downs_i;
    int ups_i;
    int rights_i;
    int As_i;
    int Bs_i;
    int message; // e.g., sugoi! warui!
    int streak;
    int points;
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
