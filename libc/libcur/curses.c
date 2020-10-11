/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * curses.c: core functions for curses library
 *
 * Curses library for CadexOS
 *
 * NOTE: This isn't the official code from
 * the developers of curses library. This is
 * completely written from scratch for CadexOS
 * using the libraries provided with CadexOS
 */

#include <curses/curses.h>

/**
 * Initializes the screen
 */
void initscr() {
    render_window(WN_STDWINDOW);
    clear_screen();
}
