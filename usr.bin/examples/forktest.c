/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include <stdio.h>

int main(int argc, const char *argv[]) {
    printf("hello world, I am %d.\n", syscall_process_self());
    int x = fork();
    printf("My fork returned %d\n", x);

    printf("Some numbers:\n");

    int i;
    for (i = 0; i < 5; ++i) {
        printf("%d\n", i);
    }
    return 0;
}
