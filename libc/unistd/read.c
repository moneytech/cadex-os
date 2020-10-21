/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include <errno.h>
#include <library/syscalls.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

int read(int file, void *ptr, size_t len) {
    __sets_errno(read_object(file, ptr, len));
}

#ifdef __cplusplus
}
#endif // __cplusplus
