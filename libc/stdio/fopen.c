#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

FILE *fopen(const char *restrict filename, int mode)
{
	FILE *f;
	int fd;
	int flags;

	int a = syscall_open_file(filename, mode, 0);
	if (!a || a == KERROR_NOT_FOUND)
	{
		return;
	}
	if (strStartsWith("/bin", filename) || strStartsWith("/usr/bin", filename) || strStartsWith("/sys", filename) || strStartsWith("/boot", filename))
		f->owner = SUPERUSER;
	f->fmode = mode;
	return f;
}

