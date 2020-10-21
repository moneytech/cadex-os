/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Standard C++ runtime functions
 * http://wiki.osdev.org/C%2B%2B
 */
#ifndef CXX__RT0
#define CXX__RT0

#include <stddef.h>

#define MAX_ATEXIT_ENTRIES 128

struct cxa_ref_s {
    void (*f)(void *);
    void *arg;
    void *dso;
};

// extern "C" int __cxa_atexit(void (*func)(void *), void *arg, void
// *dso_handle)
// {
//     if (__refs_len__ >= MAX_ATEXIT_ENTRIES)
//         return -1;
//     __refs__[__refs_len__].f = func;
//     __refs__[__refs_len__].arg = arg;
//     __refs__[__refs_len__++].dso = dso_handle;

//     return 0;
// }

extern "C" void __cxa_finalize(void *d) {
    cxa_ref_s __refs__[MAX_ATEXIT_ENTRIES];
    int __refs_len__ = 0;
    if (!d) {
        for (int i = __refs_len__ - 1; i >= 0; --i) {
            if (__refs__[i].f)
                __refs__[i].f(__refs__[i].arg);
        }
        return;
    }

    // else
    for (int i = __refs_len__ - 1; i >= 0; --i) {
        if (__refs__[i].f == d) {
            __refs__[i].f(__refs__[i].arg);
            __refs__[i].f = NULL;
        }
    }
}

#endif
