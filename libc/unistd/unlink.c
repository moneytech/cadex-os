#include <errno.h>
#include <syscall.h>
#include <syscall_nums.h>
#include <unistd.h>

DEFN_SYSCALL1(unlink, SYS_UNLINK, char*);

int unlink(const char* pathname)
{
    __sets_errno(syscall_unlink((char*)pathname));
}
