#include <truegl/truegl.h>

void TGL_window_create(tgl_window_t *window, int x, int y, int w, int h) {
    window->x = x;
    window->y = y;
    window->width = w;
    window->height = h;
    dbg_printf("<tgl> (ui_window.c:8): Creating window...\n");
}

void TGL_window_color(tgl_window_t *window, int r, int g, int b, int a){

}

void TGL_draw_window(tgl_window_t *window){
    drawRect(window->x, window->y, window->width, window->height);
    dbg_printf("<tgl> (ui_window.c:13): Drawing window... \n");
}
