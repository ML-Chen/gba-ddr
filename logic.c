#include "logic.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    /*appState->lefts = create_list();
    push_front(appState->lefts, 240);
    appState->downs = create_list();
    appState->ups = create_list();
    appState->rights = create_list();
    appState->As = create_list();
    appState->Bs = create_list();*/
    appState->gameOver = 0;
    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            appState->lefts[i] = randint(160, 210);
            appState->downs[i] = randint(160, 210);
            appState->ups[i] = randint(160, 210);
            appState->rights[i] = randint(160, 210);
            appState->As[i] = randint(160, 210);
            appState->Bs[i] = randint(160, 210);
        }
        else {
            appState->lefts[i] = randint(appState->lefts[i - 1], appState->lefts[i - 1] + 50);
            appState->rights[i] = randint(appState->rights[i - 1], appState->rights[i - 1] + 50);
            appState->downs[i] = randint(appState->downs[i - 1], appState->downs[i - 1] + 50);
            appState->ups[i] = randint(appState->ups[i - 1], appState->ups[i - 1] + 50);
            appState->As[i] = randint(appState->As[i - 1], appState->As[i - 1] + 50);
            appState->Bs[i] = randint(appState->Bs[i - 1], appState->Bs[i - 1] + 50);
        }
    }
    a->lefts_i = a->downs_i = a->ups_i = a->rights_i = a->As_i = a->Bs_i = a->message = a->streak = a->points = 0;
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
    if (KEY_JUST_PRESSED(BUTTON_UP, keysPressedNow, keysPressedBefore) || n.ups[n.ups_i] < -32) {
        handleButton(ups, ups_i)
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
        for (int i = 0; i < 9; i++) {
            n.lefts[i]--;
            n.downs[i]--;
            n.ups[i]--;
            n.rights[i]--;
            n.As[i]--;
            n.Bs[i]--;
        }
    } 

    return nextAppState;
}
