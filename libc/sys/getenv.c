/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include <stdlib.h>
#include <string.h>
#include <sys/environ.h>

extern char *getenvpath() {
    char *tok = strtok(environ[0], ",");
    return *tok;
}