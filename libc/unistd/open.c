#include <unistd.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif
	int open(const char *path, int mode, int flags)
	{
		return syscall_open_file(path, 0, flags);
	}
#ifdef __cplusplus
}
#endif