#include <debug.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

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
            syscall_debug_putc(*a);
        }
        else
        {
            a++;
            switch (*a)
            {
            case 'd':
                i = va_arg(args, int32_t);
                itoa(i, tmp);
                syscall_debug((char*)tmp);
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
                syscall_debug((const char)str);
                break;
            case '%':
                str = va_arg(args, char *);
                syscall_debug_putc('%');
                break;
            case 'c':
                u = va_arg(args, int32_t);
                syscall_debug_putc(u);
                break;
            default:
                syscall_debug_putc(*a);
                break;
            }
        }
        a++;
    }
    va_end(args);
}
