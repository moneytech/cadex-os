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
#include <library/stdint.h>

extern uintptr_t initial_esp;

typedef struct _FILE FILE;
#define __DEFINED_FILE

#define BUFSIZ 8192

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

#define EOF (-1)

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
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

#define _U 0x01  /* upper */
#define _L 0x02  /* lower */
#define _D 0x04  /* digit */
#define _C 0x08  /* cntrl */
#define _P 0x10  /* punct */
#define _S 0x20  /* white space (space/lf/tab) */
#define _X 0x40  /* hex digit */
#define _SP 0x80 /* hard space (0x20) */

_Begin_C_Header
char _ctmp;
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
void setTextColor(int r, int g, int b, int a);
void drawRect(int x, int y, int w, int h);
void clearScreen(int x, int y, int w, int h);
void drawLine(int x, int y, int w, int h);
void printChar(int x, int y, char c);
void print(int x, int y, char *s);
void flushScreen();
int getWindowDimens(char *s);
void system(char *program, int argc, char **argv);
void resetColor();



extern FILE * fopen(const char *path, const char *mode);
extern int fclose(FILE * stream);
extern int fseek(FILE * stream, long offset, int whence);
extern long ftell(FILE * stream);
extern FILE * fdopen(int fd, const char *mode);
extern FILE * freopen(const char *path, const char *mode, FILE * stream);

extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE * stream);
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE * stream);

extern int fileno(FILE * stream);
extern int fflush(FILE * stream);

extern int sprintf(char *buf, const char *fmt, ...);
extern int fprintf(FILE *stream, const char *fmt, ...);
extern int snprintf(char * buf, size_t size, const char * fmt, ...);

extern void rewind(FILE *stream);
extern void setbuf(FILE * stream, char * buf);

extern void perror(const char *s);

extern int ungetc(int c, FILE * stream);

extern int feof(FILE * stream);
extern void clearerr(FILE * stream);
extern int ferror(FILE * stream);

extern int _fwouldblock(FILE * stream);

extern FILE * tmpfile(void);

extern int setvbuf(FILE * stream, char * buf, int mode, size_t size);

extern int remove(const char * pathname);
extern int rename(const char * oldpath, const char * newpath);

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

extern char * tmpnam(char * s);
#define L_tmpnam 256


typedef long fpos_t;

extern int fgetpos(FILE *stream, fpos_t *pos);
extern int fsetpos(FILE *stream, const fpos_t *pos);


_End_C_Header;
#endif
