#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>

int isatty(int fd)
{
    int dtype = ioctl(fd, IOCTLDTYPE, NULL);
    if (dtype == IOCTL_DTYPE_TTY)
        return 1;
    errno = EINVAL;
    return 0;
}
