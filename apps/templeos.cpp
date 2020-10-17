/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * TempleOS mode
 *
 * TempleOS Mode is a mode for CadexOS that emulates TempleOS.
 */
#include <iostream>
#include <truegl/truegl.h>

using namespace std;
using namespace TGL::Core;
using namespace TGL::GKit;

int main(int argc, char *argv[]) {
    // Setup window
    setup_window();
    // Set color to blue to match TempleOS
    gui_set_bgcolor(10, 10, 100, 0);
    // Clear the screen so that it will fill the screen with blue
    clear_screen();
    /* Print the magical text interface! */
    printf("%c%c%c%c%c%c%c%c%c%c%c%c\n%c TempleOS %c\n%c%c%c%c%c%c%c%c%c%c%c%c",
           201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, 186, 186,
           200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
}
