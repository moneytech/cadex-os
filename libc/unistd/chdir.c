/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include <unistd.h>
#include <library/syscalls.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"
{
#endif
	int chdir(const char *path)
	{
		__sets_errno(syscall_chdir((char *)path));
	}
#ifdef __cplusplus
}
#endif
