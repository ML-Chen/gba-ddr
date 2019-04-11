#include "logic.h"
#include "images/title2.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->title.x = appState->title.y = appState->title.vx = appState->title.vy = 1;

    appState->gameOver = 0;
    appState->lefts[0] = 0;
    appState->rights[0] = 0;
    appState->As[0] = 0;
    appState->Bs[0] = 0;
    appState->lefts[1] = 64 + randint(1, 5) * 32;
    appState->rights[1] = 64 + randint(1, 5) * 32;
    appState->As[1] = 64 + randint(1, 5) * 32;
    appState->Bs[1] = 64 + randint(1, 5) * 32;
    for (int i = 2; i < ARRSIZE; i++) {
        appState->lefts[i] = a->lefts[i - 1] + randint(1, 5) * 32;
        appState->rights[i] = a->rights[i - 1] + randint(1, 5) * 32;
        appState->As[i] = a->As[i - 1] + randint(1, 5) * 32;
        appState->Bs[i] = a->Bs[i - 1] + randint(1, 5) * 32;
    }
    a->lefts_i = a->rights_i = a->As_i = a->Bs_i = 1;
    a->ingame = a->message = a->streak = a->points = a->time = 0;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    if (!currentAppState->ingame) {
        int x = n.title.x;
        int y = n.title.y;
        if (x <= 0 || x + TITLE2_WIDTH >= 240) n.title.vx *= -1;
        if (y <= 0 || y + TITLE2_HEIGHT >= 160) n.title.vy *= -1;

        n.title.x += n.title.vx;
        n.title.y += n.title.vy;
    } else {
        if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore) || n.lefts[n.lefts_i] < -32) {
            handleButton(lefts, lefts_i)
        }
        if (KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore) || n.rights[n.rights_i] < -32) {
            handleButton(rights, rights_i)
        }
        if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore) || n.As[n.As_i] < -32) {
            handleButton(As, As_i)
        }
        if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore) || n.Bs[n.Bs_i] < -32) {
            handleButton(Bs, Bs_i)
        }

        if (vBlankCounter % 2 == 0) {
            for (int i = 1; i < ARRSIZE; i++) {
                n.lefts[i]--;
                n.rights[i]--;
                n.As[i]--;
                n.Bs[i]--;
            }
        }
        n.time++;
        if (n.time > 5000) n.gameOver = 1;
    }

    return nextAppState;
}
