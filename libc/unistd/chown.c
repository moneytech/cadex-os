#include <errno.h>
#include <syscall.h>
#include <syscall_nums.h>
#include <unistd.h>

DEFN_SYSCALL3(chown, SYS_CHOWN, char*, int, int);

int chown(const char* pathname, uid_t owner, gid_t group)
{
    __sets_errno(syscall_chown((char*)pathname, owner, group));
}
