/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * stdio.c
 * Part of the calibc
 * Includes the most i/o functions like printf, clear_screen(), getch() ,etc.
 */
#include "stdarg.h"
#include <kernel/gfxstream.h>
#include <kernel/types.h>
#include <library/assert.h>
#include <library/math.h>
#include <library/stdbool.h>
#include <library/stdio.h>
#include <library/string.h>
#include <library/syscalls.h>

FILE _stdin = {
    .fd = 0,
    .read_buf = NULL,
    .available = 0,
    .offset = 0,
    .read_from = 0,
    .ungetc = -1,
    .eof = 0,
    .last_read_start = 0,
    .bufsiz = BUFSIZ,
};

FILE _stdout = {
    .fd = 1,
    .read_buf = NULL,
    .available = 0,
    .offset = 0,
    .read_from = 0,
    .ungetc = -1,
    .eof = 0,
    .last_read_start = 0,
    .bufsiz = BUFSIZ,
};

FILE _stderr = {
    .fd = 2,
    .read_buf = NULL,
    .available = 0,
    .offset = 0,
    .read_from = 0,
    .ungetc = -1,
    .eof = 0,
    .last_read_start = 0,
    .bufsiz = BUFSIZ,
};

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;
static char stdio_buffer[PAGE_SIZE] = {0};

static uint32_t stdio_buffer_index = 0;

static struct graphics_command graphics_buffer[PAGE_SIZE] = {{0}};

static uint32_t graphics_buffer_index = 0;

static int window_fd = WN_STDWINDOW;

void flushScreen() {
    syscall_object_write(KNO_STDOUT, stdio_buffer, stdio_buffer_index);
    stdio_buffer_index = 0;
    stdio_buffer[0] = 0;
}

static void draw_set_buffer(int t, int a0, int a1, char *a2, int a3) {
    struct graphics_command c = {t, {a0, a1, a2, a3}};
    graphics_buffer[graphics_buffer_index++] = c;
}

void flush() {
    draw_set_buffer(GRAPHICS_END, 0, 0, 0, 0);
    syscall_object_write(window_fd, graphics_buffer, graphics_buffer_index);
    graphics_buffer_index = 0;
}

// Renders the window
void render_window(int wd) {
    window_fd = wd;
    flushScreen();
    flush();
}

// Sets the text/cursor color
void setTextColor(int r, int g, int b, int a) {
    draw_set_buffer(GRAPHICS_COLOR, r, g, b, a);
    render_window(WN_STDWINDOW);
    flushScreen();
    flush();
}

void text_color(int r, int g, int b) { setTextColor(r, g, b, 100); }
void set_bg_color(int r, int g, int b, int a) {
    draw_set_buffer(GRAPHICS_BGCOLOR, r, g, b, a);
    render_window(WN_STDWINDOW);
    flushScreen();
    flush();
}
void resetColor() {
    draw_set_buffer(GRAPHICS_COLOR, 255, 255, 255, 0);
    set_bg_color(0, 43, 54, 0);
    render_window(WN_STDWINDOW);
    flush();
    flushScreen();
}
// Draws a rectangle on screen with specified dimensions
void drawRect(int x, int y, int w, int h) {
    draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
    flushScreen();
    flush();
    render_window(WN_STDWINDOW);
}

void drawTriangle(int x, int y, int w, int h) {
    draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
    flushScreen();
    flush();
}
// Clears the screen
void clearScreen(int x, int y, int w, int h) {
    draw_set_buffer(GRAPHICS_CLEAR, x, y, w, h);
    flushScreen();
    flush();
}

void clear_screen() { printf("\f"); }
// Draws a line on screen on the specified x and y axis with the specified width
// and height.
void drawLine(int x, int y, int w, int h) {
    draw_set_buffer(GRAPHICS_LINE, x, y, w, h);
    flushScreen();
    flush();
}

// Prints text on screen on the specified x and y axis.
void print(int x, int y, char *s) {
    draw_set_buffer(GRAPHICS_TEXT, x, y, s, 0);
    render_window(WN_STDWINDOW);
    flushScreen();
    flush();
}

// void perror(const char *s) {
// 	fprintf(stderr, "%s: %s\n", s, strerror(errno));
// }

int puts(const char *s) {
    /* eof? */
    printf("%s", s);
    return 0;
}

void wait_for_io(uint32_t timer_count) {
    while (1) {
        asm volatile("nop");
        timer_count--;
        if (timer_count <= 0)
            break;
    }
}

// Prints to the stdio buffer
static void printf_buffer(char *s, unsigned len) {
    while (len) {
        unsigned l = len % (PAGE_SIZE - 1);
        if (l > PAGE_SIZE - stdio_buffer_index - 1) {
            flush();
            flushScreen();
        }
        memcpy(stdio_buffer + stdio_buffer_index, s, l);
        stdio_buffer_index += l;
        len -= l;
    }
    stdio_buffer[stdio_buffer_index] = 0;
}

// Use putc instead
void printf_putchar(char c) {
    printf_buffer(&c, 1);
    if (c == '\n')
        flush();
    flushScreen();
}

void printf_putstring(char *s) { printf_buffer(s, strlen(s)); }

// Executes specified file with specified argc and argv.
void system(char *program, int argc, const char **argv) { exec(program, argc, argv); }

int setvbuf(FILE *stream, char *buf, int mode, size_t size) {
    if (mode != _IOLBF) {
        return -1; /* Unsupported */
    }
    if (buf) {
        if (stream->read_buf) {
            dlfree(stream->read_buf);
        }
        stream->read_buf = buf;
        stream->bufsiz = size;
    }
    return 0;
}
// FILE *fopen(const char *path, const char *mode)
// {

// 	int flags, mask;
// 	//parse_mode(mode, &flags, &mask);
// 	int fd = syscall_open_file(path, mode, flags);

// 	if (fd < 0)
// 	{
// 		errno = -fd;
// 		return NULL;
// 	}

// 	FILE *out = malloc(sizeof(FILE));
// 	memset(out, 0, sizeof(struct _FILE));
// 	out->fd = fd;
// 	out->read_buf = malloc(BUFSIZ);
// 	out->bufsiz = BUFSIZ;
// 	out->available = 0;
// 	out->read_from = 0;
// 	out->offset = 0;
// 	out->ungetc = -1;
// 	out->eof = 0;
// 	out->_name = strdup(path);

// 	return out;
// }

// Draws a border with the specified dimensions and color
void draw_window_border(int x, int y, int w, int h, int thickness, int r, int g,
                        int b) {
    setTextColor(r, b, g, 0);
    drawRect(x, y, w, thickness);
    drawRect(x, y, thickness, h);
    drawRect(x + w - thickness, y, thickness, h);
    drawRect(x, y + h - thickness, w, thickness);
    flush();
    flushScreen();
    // resetColor();
}

// Get a line from a file
int fgets(int fd, char *buffer[], int length) {
    return read_object(fd, buffer, length);
}

// Get char
uint8_t getch() {
    uint8_t data;
    read_object(STDIN, &data, 1);
    return data;
}
