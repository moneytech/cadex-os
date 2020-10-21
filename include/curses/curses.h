/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Curses library for CadexOS
 *
 * NOTE: This isn't the official code from
 * the developers of curses library. This is
 * completely written from scratch for CadexOS
 * using the libraries provided with CadexOS
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int x;
    int y;
} WINDOW;

void initscr();
WINDOW newwin(int height, int width, int x, int y);
