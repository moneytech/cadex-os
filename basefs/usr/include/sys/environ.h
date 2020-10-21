/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Contains the definition for enviornment variables
 */

#ifndef __ENV_H__
#define __ENV_H__
#include <types.h>

static const char *environ[] = {"PATH=/bin/;/usr/bin", "DIMG=/boot/cadex.img",
                                "KMODS=/usr/lib/libc.so;/usr/lib/libcxx.so"};

#endif // __ENV_H__