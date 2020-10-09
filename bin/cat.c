/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * The traditional cat command.
 */
#include <stdio.h>

#define TAG_BUFFER_SIZE 256
int ctemp;
int main(int argc, char *argv[]) {
    if (argc > 1) {
        syscall_chdir(argv[0]);
        // printf("got root\n");
        // int dir_fd = syscall_open_file("/", 0, 0);
        // syscall_object_set_tag(dir_fd, "ROOT");
        // printf("Opened root directory\n");
        int fd = syscall_open_file(argv[1], 0, 0);
        char buffer[1000];
        int n;
        // printf("reading file...\n");
        if (fd > 1 && fd != KERROR_NOT_FOUND) {
            while ((n = read_object(fd, buffer, 100)) > 0) {
                buffer[n] = 0;
                printf("%s", buffer);
                flush();
            }
            syscall_object_close(fd);
        } else {
            syscall_object_close(fd);
            printf("cat: error reading %s: %s\n", argv[1], strerror(fd));
            dbg_printf("[cat.exe] error reading '%s': %s\n", argv[1],
                       strerror(fd));
        }

        printf("\n");
        return 0;
    } else {
        printf("usage: cat [parent-dir] [filename]\n");
        return 0;
    }

    return 0;
}
