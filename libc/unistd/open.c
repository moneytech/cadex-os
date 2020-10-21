#include <stdarg.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
int open(const char* path, int mode)
{
    return syscall_open_file(path, mode,0);
}
#ifdef __cplusplus
}
#endif

