#ifndef __DEBUG__HH
#define __DEBUG__HH

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
    extern void dbg_printf(const char *a, ...);
#ifdef __cplusplus
}
#endif
#endif // !__DEBUG__HH