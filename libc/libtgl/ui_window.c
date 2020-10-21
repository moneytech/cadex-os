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
	/* Draw the window */
    drawRect(window->x, window->y, window->width, window->height);
    setTextColor(200, 10, 10,0);
	
	/* Draw the close button */
    drawRect(window->x + window->width - 20, window->y, 20, 20);
    resetColor();

    /* Causes error */
	// print(window->x + window->width - 15, window->y - 15, "X");

    dbg_printf("<tgl> (ui_window.c:13): Drawing window... \n");
}
