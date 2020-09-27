#include <unistd.h>
#include <library/syscalls.h>

#ifdef __cplusplus
extern "C"{
#endif

int close(int file) {
	return syscall_object_close(file);
}

#ifdef __cplusplus
}
#endif
