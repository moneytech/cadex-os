#include <iostream>
#include <truegl/truegl.h>

using namespace std;

int main(int argc, const char* argv[]) {
    tgl_window_t window;
	/* Setup console */
    setup_window();
    /* Create window */
    TGL_window_create(&window, 10, 10, 200, 200);
	/* Draw window */
    TGL_draw_window(&window);
    return 0;
}
