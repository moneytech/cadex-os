/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */
/**
 * An application to clear the screen
 */
#include <debug.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Just print out '\f' and boom! The screen is cleared!
    printf("\f");
    dbg_printf("[cls.exe] clearing the screen...\n");
    return 0;
}
