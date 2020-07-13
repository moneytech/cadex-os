/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef STDIO_H
#define STDIO_H

#include <library/syscalls.h>
#include <library/errno.h>
#include <library/types.h>
#include <library/ctype.h>
#include <library/color.h>
#include <library/const.h>
#include <library/float.h>
#include <library/hashmap.h>
#include <library/limits.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/stdbool.h>
#include <library/stddef.h>
#include <library/ascii.h>

extern uintptr_t initial_esp;

#define KNO_STDIN  0
#define KNO_STDOUT 1
#define KNO_STDERR 2
#define PAUSE                \
    {                        \
        asm volatile("hlt"); \
    }
#define STOP   \
    while (1)  \
    {          \
        PAUSE; \
    }
#define SYSCALL_VECTOR 0x7F
#define SIGNAL_RETURN 0xFFFFDEAF
#define THREAD_RETURN 0xFFFFB00F
extern char *boot_arg; /* Argument to pass to init */
extern char *boot_arg_extra;
struct asm_regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};
typedef struct asm_regs regs_t;
typedef void (*irq_handler_t)(struct asm_regs *);
typedef int (*irq_handler_chain_t)(struct asm_regs *);
#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP 0xB0000000
#define SHM_START 0xB0000000
void printf_putchar(char c);
#define WN_STDWINDOW 3
void printf_putstring(char *s);
void flush();

void renderWindow(int wd);
void setTextColor(int r, int g, int b);
void drawRect(int x, int y, int w, int h);
void clearScreen(int x, int y, int w, int h);
void drawLine(int x, int y, int w, int h);
void printChar(int x, int y, char c);
void print(int x, int y, char *s);
void flushScreen();
int getWindowDimens(char *s);

#endif
