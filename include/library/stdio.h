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
#include <library/_cheader.h>
#include <sys/root_usr.h>
#include <stdlib.h>

//extern uint8_t initial_esp;
struct _FILE
{
    int fd;

    char *read_buf;
    int available;
    int offset;
    int read_from;
    int ungetc;
    int eof;
    int bufsiz;
    int owner;
    int fmode;
    long last_read_start;
    char *_name;
    char *path;

};
typedef struct _FILE FILE;
#define __DEFINED_FILE

#define BUFSIZ 8192

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define EOF (-1)

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define KNO_STDIN 0
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

#define COS_SOURCE

_Begin_C_Header 
char _ctmp;
#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP 0xB0000000
#define SHM_START 0xB0000000


#define WN_STDWINDOW 3

extern void printf_putchar(char c);
extern void printf_putstring(char *s);
extern void flush();
extern void renderWindow(int wd);
extern void setTextColor(int r, int g, int b, int a);
extern void set_bg_color(int r, int g, int b, int a);
extern void drawRect(int x, int y, int w, int h);
extern void clearScreen(int x, int y, int w, int h);
extern void clear_screen();
extern void drawLine(int x, int y, int w, int h);
extern void printChar(int x, int y, char c);
extern void print(int x, int y, char *s);
extern void flushScreen();
extern int getWindowDimens(char *s);
extern void system(char *program, int argc, char **argv);
extern void resetColor();
extern void draw_cadex_logo(int x, int y);
extern void draw_window_border(int x, int y, int w, int h, int thickness, int r, int g, int b);

extern FILE *fopen(const char *path, int mode);
extern int fclose(FILE *stream);
extern int fseek(FILE *stream, long offset, int whence);
extern long ftell(FILE *stream);
extern FILE *fdopen(int fd, const char *mode);
extern FILE *freopen(const char *path, const char *mode, FILE *stream);

extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

extern int fileno(FILE *stream);
extern int fflush(FILE *stream);

extern int sprintf(char *buf, const char *fmt, ...);
extern int fprintf(FILE *stream, const char *fmt, ...);
extern int snprintf(char *buf, size_t size, const char *fmt, ...);

extern void rewind(FILE *stream);
extern void setbuf(FILE *stream, char *buf);

extern void perror(const char *s);

extern int ungetc(int c, FILE *stream);

extern int feof(FILE *stream);
extern void clearerr(FILE *stream);
extern int ferror(FILE *stream);

extern int _fwouldblock(FILE *stream);

extern FILE *tmpfile(void);

extern int setvbuf(FILE *stream, char *buf, int mode, size_t size);

extern int remove(const char *pathname);
extern int rename(const char *oldpath, const char *newpath);

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

extern char *tmpnam(char *s);
#define L_tmpnam 256

typedef long fpos_t;

extern int fgetpos(FILE *stream, fpos_t *pos);
extern int fsetpos(FILE *stream, const fpos_t *pos);

_End_C_Header;
#endif
