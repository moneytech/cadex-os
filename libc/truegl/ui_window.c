#include <truegl/truegl.h>

void create_window(char *title, int border_width, gui_color_t *border_color) {
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];
    char *line[1024];
    render_window(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    draw_window_border(1, 1, width - 1, height - 1, border_width,
                       border_color->r, border_color->g, border_color->b);
    print(10, 10, title);
    setTextColor(WHITE, 0);
    drawRect(0, 22, width, 3);
    flushScreen();
    flush();
}
