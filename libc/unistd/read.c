/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include <unistd.h>
#include <errno.h>
#include <library/syscalls.h>

#ifdef __cplusplus
extern "C"{
#endif

int read(int file, void *ptr, size_t len) {
	__sets_errno(read_object(file, ptr, len));
}

#ifdef __cplusplus
}
#endif // __cplusplus
