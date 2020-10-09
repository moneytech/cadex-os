/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include <library/ascii.h>
#include <library/float.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/qsort.h>
#include <library/stdio.h>
#include <library/string.h>
#include <library/strtoui.h>
#include <library/syscalls.h>

void __assert_func(const char* file, int line, const char* func, const char* failedexpr)
{
    printf("Assertion failed in %s:%d (%s): %s\n" /*, file, line, func, failedexpr*/);
    // void
}

/* EOF */
