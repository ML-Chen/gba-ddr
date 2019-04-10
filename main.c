#include "gba.h"
#include "logic.h"
#include "draw.h"
// TA-TODO: Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"
#include "images/sprites.h"
#include "images/title1.h"
#include "images/title2.h"

#include <stdio.h>
#include <stdlib.h>

volatile OamEntry shadow[128];
volatile OamEntry *left = &shadow[0];
volatile OamEntry *down = &shadow[10];
volatile OamEntry *up = &shadow[20];
volatile OamEntry *right = &shadow[30];
volatile OamEntry *A = &shadow[40];
volatile OamEntry *B = &shadow[50];

// AppState enum definition
typedef enum {
    // TA-TODO: Add any additional states you need for your app.
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

void drawSprites(void) {
    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128*4 | DMA_ON;
}

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE | SPRITES_DIMENSION_TYPE;

    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    // Sprite setup
    // Load sprite palette
    DMA[3].src = sprites_palette;
    DMA[3].dst = SPRITEPAL;
    DMA[3].cnt = SPRITES_PALETTE_LENGTH | DMA_ON;

    // Copy sprite graphic data where the GBA will expect it to be:
    DMA[3].src = sprites;
    DMA[3].dst = &CHARBLOCKBASE[5];
    DMA[3].cnt = SPRITES_LENGTH | DMA_ON;

    // Hide all sprites so that nothing funky gets drawn when the game starts:
    for (int i = 0; i < 128; i++) {
        shadow[i].attr0 = ATTR0_HIDE;
    }

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // TA-TODO: Manipulate the state machine below as needed.
        switch(state) {
            case START:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the start state here.
                drawFullScreenImageDMA(title1);
                for (int i = 0; i < 600; i++) {
                    waitForVBlank();
                }
                drawFullScreenImageDMA(title2);

                state = START_NODRAW;
                break;
            case START_NODRAW:
                // TA-TODO: Check for a button press here to start the app.
                // Start the app by switching the state to APP_INIT.
                if (KEY_DOWN(BUTTON_A, currentButtons) || KEY_DOWN(BUTTON_B, currentButtons) || KEY_DOWN(BUTTON_LEFT, currentButtons) || KEY_DOWN(BUTTON_RIGHT, currentButtons) || KEY_DOWN(BUTTON_UP, currentButtons) || KEY_DOWN(BUTTON_LEFT, currentButtons) || KEY_DOWN(BUTTON_START, currentButtons)) {
                    state = APP_INIT;
                    /*int x = 1;
                    int y = 1;
                    while (y <= 160) {
                        waitForVBlank();
                        drawImageDMA(x, y, 240, 160 - y, title2);
                        drawRectDMA(x - 1, y, 240 - x, 1, BLACK);
                        drawRectDMA(x, y - 1, 1, 160 - y, BLACK);
                        x++;
                        y++;
                    }*/
                    fillScreenDMA(GRAY);
                }

                break;
            case APP_INIT:
                // Initialize the app. Switch to the APP state.
                initializeAppState(&currentAppState);

                // Draw the initial state of the app
                fullDrawAppState(&currentAppState);

                state = APP;
                break;
            case APP:
                // Process the app for one frame, store the next state
                nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                // Wait for VBlank before we do any drawing.
                waitForVBlank();

                // Undraw the previous state
                undrawAppState(&currentAppState);

                // Draw the current state
                drawAppState(&nextAppState);

                // Now set the current state as the next state for the next iter.
                currentAppState = nextAppState;

                // Check if the app is exiting. If it is, then go to the exit state.
                if (nextAppState.gameOver) {
                    state = APP_EXIT;
                }

                break;
            case APP_EXIT:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen

                state = APP_EXIT_NODRAW;
                break;
            case APP_EXIT_NODRAW:
                // TA-TODO: Check for a button press here to go back to the start screen
                if (KEY_DOWN(BUTTON_A, currentButtons) || KEY_DOWN(BUTTON_B, currentButtons) || KEY_DOWN(BUTTON_LEFT, currentButtons) || KEY_DOWN(BUTTON_RIGHT, currentButtons) || KEY_DOWN(BUTTON_UP, currentButtons) || KEY_DOWN(BUTTON_LEFT, currentButtons) || KEY_DOWN(BUTTON_START, currentButtons)) {
                    state = START;
                }
                break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
