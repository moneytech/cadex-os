/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * errcodes.c
 *
 * IMPORTANT: must be updated as new enums are added.
 *
 * Simple test to display all error strings.
 */

#include "kernel/error.h"
#include "library/errno.h"
#include "library/string.h"

#define LOWEST_ENUM -22

int main(int argc, char **argv) {
    for (int i = 1; i >= LOWEST_ENUM; i--) {
        printf("%s\n", strerror(i));
    }
    return 0;
}
