#include <stdio.h>
#include <truegl/glx.h>
#include <truegl/events.h>
#include <truegl/truegl.h>

/**
 * Creates a TWindow with the specified dimensions
 * @param x X position of the window
 * @param y Y position of the window
 * @param w Width of the window
 * @param h Height of the window
 * @param visibility Visiblity state of the window. (1 for visible and 0 for invisible)
 * @param title Title of the window
 * @returns twindow_t
 */
twindow_t window_create(int x, int y, int w, int h, int visibility, char *title)
{
    setup_window();
    twindow_t window;
    window.properties->y = y;
    window.properties->x = x;
    window.properties->visibility = visibility;
    window.properties->top_level_window = 1;
    window.properties->height = h;
    window.properties->width = w;
    return window;
}