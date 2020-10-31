/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Manpage viewer for CadexOS
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Prints the usage
void usage() {
    printf("usage: man [path_to_manpage ...]\n");
    exit(0);
}

// Prints an error message and exits
void error(char *errmsg) {
    printf("man: error: %s\n", errmsg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 0) {
        // Arguments are 0, so print the usage.
        usage();
    }

    // We are using open() function from <unistd.h>
    int file = open(argv[0], KERNEL_FLAGS_READ);

    if (!file) {
        // Unknown error
        error("open() returned 0");
    } else if (file == KERROR_NOT_FOUND) {
        // File was not found
        printf("man: error: file '%s' not found\n", argv[0]);
    } else if (file == KERROR_NOT_A_FILE) {
        // File was a directory
        printf("man: error: '%s' is not a file\n", argv[0]);
    } else {
        // Unknown error
        printf("man: error: open() returned %d\n", file);
    }

    return 0;
}
