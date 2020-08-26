/**
 * TrueGL Graphics Library v0.2
 * 
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <stdio.h>
#include <library/scanf.h>
#include <library/_cheader.h>
#include <library/color.h>

/**
 * This enum is defined but not used. Stubbed
 */
static enum UIColor {
    T_COLOR_BLACK,
    T_COLOR_BLUE,
    T_COLOR_GREEN,
    T_COLOR_RED,
    T_COLOR_WHITE,
    T_COLOR_GRAY,
    T_COLOR_MAGENTA,
    T_COLOR_LIGHTGREEN,
    T_COLOR_LIGHTBLUE,
    T_COLOR_LIGHTGRAY
};
/**
 * GameObject type definition
*/
typedef struct
{
    int posX;
    int posY;
    int width;
    int height;
} GameObject;

/**
 * Sprite type definition
*/
typedef struct GameObject
{
    int posX;
    int posY;
    int width;
    int height;
} Sprite;

typedef struct
{
    int posX;
    int posY;
    int width;
    int height;
    char *label;
} UIElement;
/**
 * Moves the specivied sprite to the specified X and Y location
 * 
 * @param sprite Reference to the sprite to move. Must have a pointer type
 * @param x X position to move to
 * @param Y Y position to move to
*/
void moveSprite(Sprite *sprite, int x, int y);

/**
 * Resises the specified sprite to the specified width and height
 * @param sprite Reference to the sprite to resize. Must have a pointer type
 * @param width Width of the sprite to resize to
 * @param height Height of the sprite to resize to
*/
void resizeSprite(Sprite *sprite, int width, int height);