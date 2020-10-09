/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "auth.h"

extern int getAuth()
{
    char* passwd[1024];
password:
    printf("sudo: password for root: ");
    passwd_scanf(passwd, sizeof(passwd));
    if (!strcmp(passwd, "root")) {
        _process_exit(0);
        return 0;
    } else {
        printf("sudo: Wrong password\n");
        goto password;
    }
}
