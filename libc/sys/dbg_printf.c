#include <debug.h>
#include <stdarg.h>

void dbg_printf(const char *a, ...){
    va_list args;

    uint32_t u;
    int32_t i;
    char *str, tmp;

    va_start(args, a);

    while (*a)
    {
        if (*a != '%')
        {
            syscall_debug(*a);
        }
        else
        {
            a++;
            switch (*a)
            {
            case 'd':
                i = va_arg(args, int32_t);
                itoa(i, tmp);
                syscall_debug(tmp);
                break;
            case 'u':
                u = va_arg(args, uint32_t);
                itoa(u, tmp);
                syscall_debug(tmp);
                break;
            case 'x':
                u = va_arg(args, uint32_t);
                itoa(u, tmp);
                syscall_debug(tmp);
                break;
            case 's':
                str = va_arg(args, char *);
                syscall_debug(tmp);
                break;
            case '%':
                str = va_arg(args, char *);
                syscall_debug("%");
                break;
            case 'c':
                u = va_arg(args, int32_t);
                syscall_debug(u);
                break;
            default:
                syscall_debug(*a);
                break;
            }
        }
        a++;
    } 
    va_end(args);
}