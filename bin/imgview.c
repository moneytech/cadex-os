/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Image viewer. Loads the specified image from disk and shows it on the
 * console.
 */

#include <libbmp/bitmap.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    /* Check the command-line args */
    if (argc > 0) {
        printf("Reading image %s...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", argv[0]);
        // clear_screen();
        if (strcmp(argv[0], "imgview"))
            if (!readBMP(argv[0],100,10))
                printf("error: readBMP() returned 1\n");
            else
                getch();
    } else {
        printf("usage: imgview [path ...]\n");
    }

    return 0;
}
