#include <kernel/types.h>

#define ASSUME(cond) __extension__({ if (!(cond)) { __builtin_unreachable(); } })
#define PAUSE                \
    {                        \
        asm volatile("hlt"); \
    }

#define STOP   \
    while (1)  \
    {          \
        PAUSE; \
    }

#define SYSCALL_VECTOR 0x43
#define SIGNAL_RETURN 0xFFFFDEAF
#define THREAD_RETURN 0xFFFFB00F