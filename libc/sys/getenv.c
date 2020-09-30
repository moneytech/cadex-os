/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include <stdlib.h>
#include <sys/environ.h>
#include <string.h>

extern char *getenvpath(){
    char *tok = strtok(environ[0], ",");
    return *tok;
}