/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * The traditional cat command.
 */
#include <stdio.h>

#define TAG_BUFFER_SIZE 256

int n;
char buffer[1000];

int main(int argc, char *argv[]) {
    if (argc > 0) {
        syscall_chdir("/");
        int fd = syscall_open_file(argv[0], 0, 0);
        // printf("reading file...\n");
        if (fd > 1 && fd != KERROR_NOT_FOUND) {
            while ((n = read_object(fd, buffer, 100)) > 0) {
                buffer[n] = 0;
                printf("%s", buffer);
                flush();
            }
            syscall_object_close(fd);
        }else if (fd == KERROR_NOT_FOUND)
        {
            printf("cat: error: %s: no such file or directory\n");
            exit(0);
        } else {
            syscall_object_close(fd);
            printf("cat: error: unable to read '%s': %s\n", argv[0], strerror(fd));
        }

        printf("\n");
        return 0;
    } else {
        printf("usage: cat [parent-dir] [filename]\n");
        return 0;
    }

    return 0;
}
