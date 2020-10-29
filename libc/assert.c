/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include <stdio.h>

void __assert_func(const char *file, int line, const char *func,
                   const char *failedexpr) {
    PANIC("PANIC(%d): Assertion failed in %s:%d (%s): %s\n" ,__LINE__, file, line, func, failedexpr);
    // void
}

/* EOF */
