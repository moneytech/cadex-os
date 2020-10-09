/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "stdarg.h"
#include <kernel/gfxstream.h>
#include <kernel/types.h>
#include <library/assert.h>
#include <library/math.h>
#include <library/stdbool.h>
#include <library/stdio.h>
#include <library/string.h>
#include <library/syscalls.h>
#include <stdlib.h>

// TODO: Move some code from stdio.c to stdlib.c

void exit(int status)
{
    _process_exit(status);
    return;
}
