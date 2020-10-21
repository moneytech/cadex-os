/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Startup Application
 *
 * Startup Application is responsible for choosing
 * which application should start after the system
 * has booted up.
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    int index;
    int temp;
    uint8_t buffer[1024];

    dbg_printf(
        "[stapp.exe] checking for kshell config file in /etc/kshell.cfg... ");
    // TODO: Implement stapp functionality
    dbg_printf("ok\n");
    return 0;
}
