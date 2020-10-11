/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
    syscall_chdir("/");

    int dir_fd = syscall_open_file("/", 0, 0);
    syscall_object_set_tag(dir_fd, "C");

    int fd = syscall_open_file("C:/data/words", 0, 0);
    char buffer[1000];
    int n;

    while ((n = read_object(fd, buffer, 100)) > 0) {
        buffer[n] = 0;
        printf("%s", buffer);
    }

	syscall_object_close(fd);
    return 0;
}
