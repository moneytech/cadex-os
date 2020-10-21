/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Fake splash screen for manager.exe
 */

#include <libbmp/bitmap.h>
#include <stdio.h>
#include <truegl/truegl.h>

int main(int argc, const char *argv[]) {
    int x1 = 12;
    int y1 = 12;
    int dims[2];
    char stop = -1;
    int i = 0;

    syscall_object_size(WN_STDWINDOW, &dims, 2);

    setup_window();
    gui_set_bgcolor(255, 255, 255, 0);
    setTextColor(0, 0, 0, 0);
    clear_screen();
    readBMP("/usr/share/splash.bmp", 150, dims[1] / 2 - 120);
    resetColor();
    getch();
    return 0;
}
