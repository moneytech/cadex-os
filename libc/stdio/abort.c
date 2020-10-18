#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

__attribute__((__noreturn__)) void abort(void)
{
    // TODO: Abnormally terminate the process as if by SIGABRT.
    printf("abort()\n");
    dbg_printf("abort(): called by a userspace program\n");
    while (1)
    {
    }
    __builtin_unreachable();
}
