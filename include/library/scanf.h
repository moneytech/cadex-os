/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/ctype.h>
#include <library/ascii.h>

#ifdef __cplusplus
extern "C" {
#endif
int scanf(char *line, int length);
int passwd_scanf(char *line, int length);

#ifdef __cplusplus
}
#endif