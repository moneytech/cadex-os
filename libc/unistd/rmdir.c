#include <errno.h>
#include <unistd.h>

int rmdir(const char* pathname)
{
    errno = ENOTSUP;
    return -1;
}
