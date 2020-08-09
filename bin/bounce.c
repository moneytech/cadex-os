/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/* An application to make graphical dialogs */
#include <library/stdio.h>
#include <library/color.h>
#include <library/types.h>


int main(int argc, char const *argv[])
{
    int r = 255;
    int g = 0;
    int b = 0;
    int x1 = 12;
    int y1 = 12;
    int dx1 = 4;
    int dy1 = 1;
    int dr = -1;
    int dg = 2;
    int db = 3;
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];

    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    flush();
    setTextColor(GREEN, 0);
    setTextColor(WHITE, 0);
    print(x1, y1, "Bounce - a small game");
    resetColor();
    flush();
    return 0;
}
