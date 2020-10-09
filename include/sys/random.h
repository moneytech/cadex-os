/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#ifndef _SYS_RANDOM_H
#define _SYS_RANDOM_H
#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_size_t
#define __NEED_ssize_t
#include <bits/alltypes.h>

#define GRND_NONBLOCK	0x0001
#define GRND_RANDOM	0x0002

size_t getrandom(void *, size_t, unsigned);

#ifdef __cplusplus
}
#endif
#endif