#include <errno.h>
#include <sys/stat.h>
#include <syscall.h>
#include <syscall_nums.h>

DEFN_SYSCALL2(chmod, SYS_CHMOD, char*, int);

int chmod(const char* path, mode_t mode)
{
    __sets_errno(syscall_chmod((char*)path, mode));
}
