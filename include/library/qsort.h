/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include <library/const.h>
#include <library/ctype.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/stdio.h>
#include <library/syscalls.h>

extern void qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));
