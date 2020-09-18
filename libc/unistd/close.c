#include <unistd.h>
#include <library/syscalls.h>

int close(int file) {
	return syscall_object_close(file);
}
