#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int access(const char* pathname, int mode)
{
    int result = syscall_access((char*)pathname, mode);
    if (result < 0) {
        errno = ENOENT; /* XXX */
        return -1;
    }
    return result;
}
