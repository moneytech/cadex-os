#include <stdarg.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
int open(const char *path, kernel_flags_t flags) {
    return syscall_open_file(path, 0, flags);
}
#ifdef __cplusplus
}
#endif
