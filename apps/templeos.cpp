/**
 * Copyright (C) 2019-2020 The CadexOS Project
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

char c;
int integeroveflowexceptionandsegmentationfaultwithcoredumpedintoconsole;

int main(int argc, char *argv[]) {
    // Setup window
    setup_window();
    // Set color to blue to match TempleOS
    gui_set_bgcolor(10, 10, 100, 0);
    // Clear the screen so that it will fill the screen with blue
    clear_screen();
    /* Print the magical text interface! */
    printf("%c%c%c%c%c%c%c%c%c%c%c%c\n%c TempleOS "
           "%c\n%c%c%c%c%c%c%c%c%c%c%c%c\n\nGod doodle: Press space "
           "continously.\n\n",
           201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, 186, 186,
           200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    while (1) {
        read_object(0, &c, 1);
        if (c == 0x20) {
            drawLine(rand(1, 100), rand(1, 100), rand(1, 3), rand(1, 100));
            dbg_printf(
                "[templeos] Drawn %d line\n",
                integeroveflowexceptionandsegmentationfaultwithcoredumpedintoconsole);
            integeroveflowexceptionandsegmentationfaultwithcoredumpedintoconsole++;
        }
    }
}
