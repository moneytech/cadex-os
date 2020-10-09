#include <sys/types.h>
#include <syscall.h>
#include <syscall_nums.h>

DEFN_SYSCALL1(setuid, SYS_SETUID, unsigned int);

int setuid(uid_t uid)
{
    return syscall_setuid(uid);
}
