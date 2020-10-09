/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Utitlity for checking if the filesystem works or not
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (syscall_open_file("/sys/reg.json", 0, 0) < 0)
        return 1;
    else
        return 0;
}
