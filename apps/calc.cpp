/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * This is an example for using TrueGL libraries and libbmp
 *
 * FYI:
 * * libbmp is the library used for reading and displaying bitmap (.bmp) images
 *   from disk
 * * TrueGL is the library used for making graphical windows.
 */

#include <iostream>
#include <libbmp/bitmap.h>
#include <truegl/truegl.h>

using namespace std;

int main(int argc, const char *argv[]) {
    tgl_window_t window;
    /* Setup console */
    setup_window();
    /* Create window */
    TGL_window_create(&window, 10, 10, 200, 200);
    /* Draw window */
    TGL_draw_window(&window);
	/* Clear the screen */
    clear_screen();
	/* Show a bitmap image from file */
    readBMP("/usr/share/test.bmp",10,10);
    /* read 1 character from keyboard */
    getch();
	/* print a newline */
    printf("\n%c",256);
    return 0;
}
