/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "library/stdio.h"
#include "library/string.h"
#include "library/syscalls.h"

int main(int argc, char* argv[])
{
    syscall_chdir("/");
    printf("got root\n");
    int dir_fd = syscall_open_file("/", 0, 0);
    syscall_object_set_tag(dir_fd, "ROOT");
    printf("Opened root directory\n");
    int fd = syscall_open_file("ROOT:/data/words", 0, 0);
    char buffer[1000];
    int n;
    printf("reading file...\n");
    while ((n = read_object(fd, buffer, 100)) > 0) {
        buffer[n] = 0;
        printf("%s", buffer);
        flush();
    }
    syscall_object_close(fd);
    _process_exit(0);

    return 0;
}
