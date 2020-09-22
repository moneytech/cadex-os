/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#pragma once

#include <library/_cheader.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define COS_SOURCE // Define that this is Cadex-OS source

#ifndef NDEBUG
    extern void
    __assert_func(const char *file, int line, const char *func, const char *failedexpr);
#define assert(statement) ((statement) ? (void)0 : __assert_func(__FILE__, __LINE__, __FUNCTION__, #statement))
#else
#define assert(statement) ((void)0)
#endif

#ifdef __cplusplus
}
#endif
