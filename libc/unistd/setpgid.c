#include <errno.h>
#include <syscall.h>
#include <syscall_nums.h>
#include <unistd.h>

DEFN_SYSCALL2(setpgid, SYS_SETPGID, int, int);
DEFN_SYSCALL1(getpgid, SYS_GETPGID, int);

int setpgid(pid_t pid, pid_t pgid)
{
    __sets_errno(syscall_setpgid((int)pid, (int)pgid));
}

pid_t getpgid(pid_t pid)
{
    __sets_errno(syscall_getpgid((int)pid));
}
