/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/*
A fun graphics demo that features a line segment bouncing around the screen.
*/

#include <stdio.h>

#define WIDTH  (200)
#define HEIGHT (200)

int main(int argc, char *argv[]) {
    render_window(WN_STDWINDOW);
    setTextColor(0, 0, 255, 0);
    clear_screen();

    int console = syscall_open_console(WN_STDWINDOW);
    if (console < 0) {
        printf("Console open failed!\n");
        return 2;
    }

    syscall_object_dup(console, STDOUT);
    printf("Hello World!\n");

    return 0;
}
