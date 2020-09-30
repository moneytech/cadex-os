#ifndef __DEBUG__HH
#define __DEBUG__HH

#include <stdio.h>

static inline void dbg_printf(const char *a){
    syscall_debug(a);
}

#endif // !__DEBUG__HH