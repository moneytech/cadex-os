/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#include "kprintf.h"
#include "console.h"
#include "keyboard.h"
#include "string.h"
#include <stdarg.h>

#define DEBUG 0
#define ESC 0x1b

static void enable_serial_color()
{
    outb(ESC, COM1);
    outb('[', COM1);
    outb('3', COM1);
    outb('6', COM1);
    outb('m', COM1);
}

static void disable_serial_color()
{
    outb(ESC, COM1);
    outb('[', COM1);
    outb('0', COM1);
    outb('m', COM1);
}

static void printf_putchar(char c)
{
    console_putchar(&console_root, c);
}

char getchar()
{
    return keyboard_read(0);
}

void putchar(char c)
{
    return printf_putchar(c);
}

static void printf_putstring(char* s)
{
    console_putstring(&console_root, s);
}

static void printf_puthexdigit(uint8_t i)
{
    if (i < 10) {
        printf_putchar('0' + i);
    } else {
        printf_putchar('a' + i - 10);
    }
}

static void printf_puthex(uint32_t i)
{
    int j;
    for (j = 28; j >= 0; j = j - 4) {
        printf_puthexdigit((i >> j) & 0x0f);
    }
}

static void serial_puthexdigit(uint8_t i) {
    if (i < 10) {
        serial_write(0, '0' + i);
    } else {
        serial_write(0, 'a' + i - 10);
    }
}

static void serial_puthex(uint32_t i) {
    int j;
    for (j = 28; j >= 0; j = j - 4) {
        serial_puthexdigit((i >> j) & 0x0f);
    }
}

static void printf_putint(int32_t i)
{
    int f, d;
    if (i < 0 && i != 0) {
        printf_putchar('-');
        i = -i;
    }

    f = 1;
    while ((i / f) >= 10) {
        f *= 10;
    }
    while (f > 0) {
        d = i / f;
        printf_putchar('0' + d);
        i = i - d * f;
        f = f / 10;
    }
}

static void printf_putuint(uint32_t u)
{
    int f, d;
    f = 1;
    while ((u / f) >= 10) {
        f *= 10;
    }
    while (f > 0) {
        d = u / f;
        printf_putchar('0' + d);
        u = u - d * f;
        f = f / 10;
    }
}

void kprintf(const char* s, ...)
{
    va_list args;

    uint32_t u;
    int32_t i;
    char* str;

    va_start(args, s);

    while (*s) {
        if (*s != '%') {
            printf_putchar(*s);
        } else {
            s++;
            switch (*s) {
            case 'd':
                i = va_arg(args, int32_t);
                printf_putint(i);
                break;
            case 'u':
                u = va_arg(args, uint32_t);
                printf_putuint(u);
                break;
            case 'x':
                u = va_arg(args, uint32_t);
                printf_puthex(u);
                break;
            case 's':
                str = va_arg(args, char*);
                printf_putstring(str);
                break;
            case 'c':
                u = va_arg(args, int32_t);
                printf_putchar(u);
                break;
			case 'n':
                u = va_arg(args, uint8_t);
                printf_putchar(u);
                break;
            case 0:
                return;
                break;
            default:
                printf_putchar(*s);
                break;
            }
        }
        s++;
    }
    va_end(args);
}

void dbg_printf(const char* s, ...)
{
    va_list args;

    uint32_t u;
    int32_t i;
    char* str;

    va_start(args, s);

    // Enable serial output coloring
    // enable_serial_color();

    while (*s) {
        if (*s != '%') {
            serial_write(0, *s);
        } else {
            s++;
            switch (*s) {
            case 'd':
                i = va_arg(args, int32_t);
                char* tmp;
                itoa(i, tmp);
                serial_device_write(0, tmp, strlen(tmp), 0);
                break;
            case 'u':
                u = va_arg(args, uint32_t);
                serial_device_write(0, u, sizeof(u), 0);
                break;
            case 'x':
                u = va_arg(args, uint32_t);
                serial_puthex(u);
                break;
            case 's':
                str = va_arg(args, char*);
                serial_device_write(0, str, strlen(str), 0);
                break;
            case 'c':
                u = va_arg(args, int32_t);
                serial_write(0, u);
                break;
            case 0:
                return;
                break;
            default:
                serial_write(0, *s);
                break;
            }
        }
        s++;
    }
    va_end(args);

    // Disable serial output coloring
    // disable_serial_color();
}

/* Systemd like success messages */
void w_ok_status(char* s)
{
    struct graphics_color g;
    g.a = 0;
    g.b = 10;
    g.g = 200;
    g.r = 10;
    kprintf("[ ");
    graphics_fgcolor(&graphics_root, g);
    kprintf("OK");
    g.a = 0;
    g.b = 255;
    g.g = 255;
    g.r = 255;
    graphics_fgcolor(&graphics_root, g);
    kprintf(" ]  %s", s);
}

void w_fail_status(char* s)
{
    struct graphics_color g;
    g.a = 0;
    g.b = 10;
    g.g = 10;
    g.r = 250;
    kprintf("[ ");
    graphics_fgcolor(&graphics_root, g);
    kprintf("FAIL");
    g.a = 0;
    g.b = 255;
    g.g = 255;
    g.r = 255;
    graphics_fgcolor(&graphics_root, g);
    kprintf(" ]  %s", s);
}

