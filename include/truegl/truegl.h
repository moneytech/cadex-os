/**
 * TrueGL Graphics Library v0.2
 *
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
 */

#include <library/_cheader.h>
#include <library/color.h>
#include <library/scanf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This enum is defined but not used. Stubbed
 */
enum UIColor {
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
typedef struct {
    int posX;
    int posY;
    int width;
    int height;
} GameObject;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} gui_color_t;

/**
 * Sprite type definition
 */
typedef struct {
    int posX;
    int posY;
    int width;
    int height;
} Sprite;

typedef struct {
    int posX;
    int posY;
    int width;
    int height;
    char *label;
} UIElement;

typedef struct {
    /* Window size */
    uint32_t width;
    uint32_t height;

    /* Window backing buffer */
    char *buffer;

    /* Window focused flag */
    uint8_t focused;

    /* Window position */
    int32_t x;
    int32_t y;

    /* Window border color */
    gui_color_t *border_color;

	/* Root window flag */
} tgl_window_t;

/* Get window and objects */
#define get_object(w) ((struct GameObject *)w)
#define get_window(w) ((tgl_window_t *)w)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Moves the specivied sprite to the specified X and Y location
 *
 * @param sprite Reference to the sprite to move. Must have a pointer type
 * @param x X position to move to
 * @param Y Y position to move to
 */
void move_sprite(Sprite *sprite, int x, int y);

/**
 * Resises the specified sprite to the specified width and height
 * @param sprite Reference to the sprite to resize. Must have a pointer type
 * @param width Width of the sprite to resize to
 * @param height Height of the sprite to resize to
 */
void resize_sprite(Sprite *sprite, int width, int height);

/* Internal function. Used as a base for other functions */
int movable_scanf(int x, int y, char *line, int length);

/**
 * Draws a pixel at the specified position with the specified color
 */
void draw_pixel(int x, int y, int r, int g, int b, int a);
void create_edittext(int x, int y, int w, int h, char *placeholder, char *line);

/**
 * Draws a graphical button with specified dimensions
 */
int draw_button(int x, int y, int w, int h, char *label);

/**
 * Draws a static textarea at the specified position with specified placeholder
 */
int draw_static_textarea(char *placeholder);

/**
 * Sets up the console for graphical functions
 */
void setup_window();

#ifdef __cplusplus
}
#endif
