/**
 * TrueGL Graphics Library v0.2
 *
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
 */

#include <debug.h>
#include <truegl/events.h>
#include <truegl/truegl.h>

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
void move_sprite(Sprite *sprite, int x, int y) {
    sprite->posX = x;
    sprite->posY = y;
}

/**
 * Resises the specified sprite to the specified width and height
 * @param sprite Reference to the sprite to resize. Must have a pointer type
 * @param width Width of the sprite to resize to
 * @param height Height of the sprite to resize to
 */
void resize_sprite(Sprite *sprite, int width, int height) {
    sprite->height = height;
    sprite->width = width;
}

void draw_pixel(int x, int y, int r, int g, int b, int a) {
    setTextColor(r, g, b, a);
    drawRect(x, y, 1, 1);
}

int get_mouse_down() { return 0; }

/**
 * Sets up the console for graphical functions
 */
void setup_window() {
    render_window(WN_STDWINDOW);
    clear_screen();
    dbg_printf("<tgl> (tgl_base.c:53): setting up window...\n");
}

// Function to put pixels
// at subsequence points
void drawCircle(int xc, int yc, int x, int y) {
    drawRect(xc + x, yc + y, 1, 1);
    drawRect(xc - x, yc + y, 1, 1);
    drawRect(xc + x, yc - y, 1, 1);
    drawRect(xc - x, yc - y, 1, 1);
    drawRect(xc + y, yc + x, 1, 1);
    drawRect(xc - y, yc + x, 1, 1);
    drawRect(xc + y, yc - x, 1, 1);
    drawRect(xc - y, yc - x, 1, 1);
}

// Function for circle-generation
// using Bresenham's algorithm
void draw_circle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x) {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
}
#ifdef __cplusplus
}
#endif
