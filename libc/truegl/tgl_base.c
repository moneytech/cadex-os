/**
 * TrueGL Graphics Library v0.2
 *
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <debug.h>
#include <truegl/events.h>
#include <truegl/truegl.h>

/**
 * Moves the specivied sprite to the specified X and Y location
 *
 * @param sprite Reference to the sprite to move. Must have a pointer type
 * @param x X position to move to
 * @param Y Y position to move to
*/
void move_sprite(Sprite* sprite, int x, int y)
{
    sprite->posX = x;
    sprite->posY = y;
}

/**
 * Resises the specified sprite to the specified width and height
 * @param sprite Reference to the sprite to resize. Must have a pointer type
 * @param width Width of the sprite to resize to
 * @param height Height of the sprite to resize to
*/
void resize_sprite(Sprite* sprite, int width, int height)
{
    sprite->height = height;
    sprite->width = width;
}

void draw_pixel(int x, int y, int r, int g, int b, int a)
{
    setTextColor(r, g, b, a);
    drawRect(x, y, 1, 1);
}

int get_mouse_down()
{
    return 0;
}

void setup_window()
{
    renderWindow(WN_STDWINDOW);
    clear_screen();
    dbg_printf("<tgl> (tgl_base.c:53): setting up window...\n");
}

