#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/ctype.h>
#include <library/ascii.h>

#ifdef __cplusplus
extern "C" {
#endif
int scanf(char *line, int length);
int passwd_scanf(char *line, int length);

#ifdef __cplusplus
}
#endif