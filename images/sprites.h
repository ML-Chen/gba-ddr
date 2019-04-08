/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=4 --for_bitmap --transparent=FFFFFF sprites left.png down.png up.png right.png A.png B.png 
 * Time-stamp: Monday 04/08/2019, 04:04:56
 * 
 * Image Information
 * -----------------
 * left.png 32@32
 * down.png 32@32
 * up.png 32@32
 * right.png 32@32
 * A.png 32@32
 * B.png 32@32
 * Transparent color: (255, 255, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (0 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[256];
#define SPRITES_PALETTE_SIZE 512
#define SPRITES_PALETTE_LENGTH 256

extern const unsigned short sprites[1536];
#define SPRITES_SIZE 3072
#define SPRITES_LENGTH 1536

#define LEFT_PALETTE_ID (0 << 12)
#define LEFT_SPRITE_SHAPE (0 << 14)
#define LEFT_SPRITE_SIZE (2 << 14)
#define LEFT_ID 512

#define DOWN_PALETTE_ID (0 << 12)
#define DOWN_SPRITE_SHAPE (0 << 14)
#define DOWN_SPRITE_SIZE (2 << 14)
#define DOWN_ID 528

#define UP_PALETTE_ID (0 << 12)
#define UP_SPRITE_SHAPE (0 << 14)
#define UP_SPRITE_SIZE (2 << 14)
#define UP_ID 544

#define RIGHT_PALETTE_ID (0 << 12)
#define RIGHT_SPRITE_SHAPE (0 << 14)
#define RIGHT_SPRITE_SIZE (2 << 14)
#define RIGHT_ID 560

#define A_PALETTE_ID (0 << 12)
#define A_SPRITE_SHAPE (0 << 14)
#define A_SPRITE_SIZE (2 << 14)
#define A_ID 576

#define B_PALETTE_ID (0 << 12)
#define B_SPRITE_SHAPE (0 << 14)
#define B_SPRITE_SIZE (2 << 14)
#define B_ID 592

#endif

