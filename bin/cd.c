/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * cd: utility to change currend working directory
*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc > 0) {
        chdir(argv[0]);
    } else {
        printf("usage: cd <path>\n");
    }
    return 0;
}
