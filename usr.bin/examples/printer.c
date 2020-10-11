/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/*
A fun graphics demo that features a line segment bouncing around the screen.
*/

#include "library/stdio.h"
#include "library/string.h"
#include "library/syscalls.h"

#define WIDTH (200)
#define HEIGHT (200)

int main(int argc, char* argv[])
{
    renderWindow(WN_STDWINDOW);
    setTextColor(0, 0, 255,0);
    clearScreen(0, 0, WIDTH, HEIGHT);
    flush();

    int cd = syscall_open_console(WN_STDWINDOW);
    if (cd < 0) {
        printf("Console open failed!\n");
        return 2;
    }
    syscall_object_dup(cd, KNO_STDOUT);

    printf("hello world!\n");

    return 0;
}
