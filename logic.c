#include "logic.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->gameOver = 0;
    appState->lefts[0] = 0;
    appState->downs[0] = 0;
    appState->As[0] = 0;
    appState->Bs[0] = 0;
    for (int i = 1; i < ARRSIZE; i++) {
        appState->lefts[i] = a->lefts[i - 1] + randint(50, 160);
        appState->downs[i] = a->downs[i - 1] + randint(50, 160);
        appState->As[i] = a->As[i - 1] + randint(50, 160);
        appState->Bs[i] = a->Bs[i - 1] + randint(50, 160);
    }
    a->lefts_i = a->downs_i = a->As_i = a->Bs_i = 1; a->message = a->streak = a->points = 0;
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

    if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore) || n.lefts[n.lefts_i] < -32) {
        handleButton(lefts, lefts_i)
    }
    if (KEY_JUST_PRESSED(BUTTON_DOWN, keysPressedNow, keysPressedBefore) || n.downs[n.downs_i] < -32) {
        handleButton(downs, downs_i)
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
            n.downs[i]--;
            n.As[i]--;
            n.Bs[i]--;
        }
    }

    if (vBlankCounter > 5000) n.gameOver = 1;

    return nextAppState;
}
