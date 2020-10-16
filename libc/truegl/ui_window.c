#include <truegl/truegl.h>

void TGL_window_create(tgl_window_t *window, int x, int y, int w, int h) {
    window->x = x;
    window->y = y;
    window->width = w;
    window->height = h;
}

void TGL_draw_window(tgl_window_t *window){
    drawRect(window->x, window->y, window->width, window->height);
}
