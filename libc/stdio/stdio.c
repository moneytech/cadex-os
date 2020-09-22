/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/*
* stdio library
* part of the libc
* includes the most i/o functions like print, setTextColor
* this is not the stdio in GNU libc. that is different
*/
#include <kernel/gfxstream.h>
#include <kernel/types.h>
#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/string.h>
#include <library/stdbool.h>
#include <library/math.h>
#include <library/assert.h>
#include "stdarg.h"



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

void flushScreen()
{
	syscall_object_write(KNO_STDOUT, stdio_buffer, stdio_buffer_index);
	stdio_buffer_index = 0;
	stdio_buffer[0] = 0;
}

static void draw_set_buffer(int t, int a0, int a1, char *a2, int a3)
{
	struct graphics_command c = {t, {a0, a1, a2, a3}};
	graphics_buffer[graphics_buffer_index++] = c;
}

void flush()
{
	draw_set_buffer(GRAPHICS_END, 0, 0, 0, 0);
	syscall_object_write(window_fd, graphics_buffer, graphics_buffer_index);
	graphics_buffer_index = 0;
}

// Renders the window
void renderWindow(int wd)
{
	window_fd = wd;
	flushScreen();
	flush();
}

// Sets the text/cursor color
void setTextColor(int r, int g, int b, int a)
{
	draw_set_buffer(GRAPHICS_COLOR, r, g, b, a);
	flushScreen();
	flush();
	renderWindow(WN_STDWINDOW);
}
void resetColor()
{
	draw_set_buffer(GRAPHICS_COLOR, 255, 255, 255, 0);
	flush();
}
// Draws a rectangle on screen with specified dimensions
void drawRect(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
	flushScreen();
	flush();
	renderWindow(WN_STDWINDOW);
}

void drawTriangle(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
	flushScreen();
	flush();
}
// Clears the screen
void clearScreen(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_CLEAR, x, y, w, h);
	flushScreen();
	flush();
}

void clear_screen(){
	printf("\f");
}
// Draws a line on screen on the specified x and y axis with the specified width and height.
void drawLine(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_LINE, x, y, w, h);
	flushScreen();
	flush();
}

// Prints text on screen on the specified x and y axis.
void print(int x, int y, char *s)
{
	draw_set_buffer(GRAPHICS_TEXT, x, y, s, 0);
	flushScreen();
	flush();
}

// void perror(const char *s) {
// 	fprintf(stderr, "%s: %s\n", s, strerror(errno));
// }

int puts(const char *s)
{
	/* eof? */
	printf(s);
	return 0;
}

// Prints text on screen on the specified x and y axis.
void print_debug(int x, int y, char *s)
{
#ifdef DEBUG
	draw_set_buffer(GRAPHICS_TEXT, x, y, (int)s, 0);
	flushScreen();
#endif // DEBUG
}

// Get data from specified port.
uint8_t inb(uint16_t port)
{
	uint8_t data;
	asm volatile("inb %1, %0"
				 : "=a"(data)
				 : "Nd"(port));
	return data;
}

// Send data to specified port.
void outb(uint16_t port, uint8_t data)
{
	asm volatile("outb %0, %1"
				 :
				 : "a"(data), "Nd"(port));
}
void wait_for_io(uint32_t timer_count)
{
	while (1)
	{
		asm volatile("nop");
		timer_count--;
		if (timer_count <= 0)
			break;
	}
}

static void printf_buffer(char *s, unsigned len)
{
	while (len)
	{
		unsigned l = len % (PAGE_SIZE - 1);
		if (l > PAGE_SIZE - stdio_buffer_index - 1)
		{
			flush();
			flushScreen();
		}
		memcpy(stdio_buffer + stdio_buffer_index, s, l);
		stdio_buffer_index += l;
		len -= l;
	}
	stdio_buffer[stdio_buffer_index] = 0;
}

void printf_putchar(char c)
{
	printf_buffer(&c, 1);
	if (c == '\n')
		flush();
	flushScreen();
}

void printf_putstring(char *s)
{
	printf_buffer(s, strlen(s));
}

// Sets the CPU to noop mode for specified milliseconds
void sleep(uint32_t timer_count)
{
	wait_for_io(timer_count * 0x02FFFFFF);
}

// Play sound with specified frequency
static void play_sound(uint32_t nFrequence)
{
	uint32_t Div;
	uint8_t tmp;

	//Set the PIT to the desired frequency
	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t)(Div));
	outb(0x42, (uint8_t)(Div >> 8));

	//And play the sound using the PC speaker
	tmp = inb(0x61);
	if (tmp != (tmp | 3))
	{
		outb(0x61, tmp | 3);
	}
}

// Stop playing sound
static void nosound()
{
	uint8_t tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}

// A code for Beeping. May not work correctly on QEMU. See https://wiki.osdev.org/PC_Speaker#Sample_Code/
void beep()
{
	play_sound(1000);
	sleep(10);
	nosound();
	//set_PIT_2(old_frequency);
}
// End sound code

// Returns Window Dimensions. EXPERIMENTAL
int getWindowDimens(char *type)
{
	int dims[2];
	syscall_object_size(WN_STDWINDOW, dims, 2);

	int width = dims[0];
	int height = dims[1];
	if (!strcmp(type[0], "width"))
	{
		return width;
	}
	if (!strcmp(type[0], "height"))
	{
		return height;
	}
	return width, height;
}

// Executes specified file with specified argc and argv.
void system(char *program, int argc, char **argv)
{
	exec(program, argc, argv);
}

void __stdio_init_buffers(void)
{
	_stdin.read_buf = malloc(BUFSIZ);
	//_stdout.read_buf = malloc(BUFSIZ);
	//_stderr.read_buf = malloc(BUFSIZ);
	_stdin._name = strdup("stdin");
	_stdout._name = strdup("stdout");
	_stderr._name = strdup("stderr");
}
int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
	if (mode != _IOLBF)
	{
		return -1; /* Unsupported */
	}
	if (buf)
	{
		if (stream->read_buf)
		{
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
/**
 * Draws a border with the specified dimensions and color
 * @param x
 * @param y
*/
void draw_window_border(int x, int y, int w, int h, int thickness, int r, int g, int b)
{
	setTextColor(r, b, g, 0);
	drawRect(x, y, w, thickness);
	drawRect(x, y, thickness, h);
	drawRect(x + w - thickness, y, thickness, h);
	drawRect(x, y + h - thickness, w, thickness);
	flush();
	flushScreen();
	//resetColor();
}

/**
 * Draw the Cadex OS Logo to the console
 * @param x The x position of logo
 * @param y The y position of the logo
*/
void draw_cadex_logo(int x, int y)
{
	renderWindow(WN_STDWINDOW);
	drawRect(x, y, 50, 50);
	setTextColor(GREEN, 0);
	drawRect(x, y, 40, 40);
	setTextColor(CLEAR_RED, 0);
	drawRect(x, y, 30, 30);
	setTextColor(BLUE, 0);
	drawRect(x, y, 20, 20);
	setTextColor(GRAY, 0);
	drawRect(x, y, 10, 10);
	flushScreen();
	flush();
}

/**
 * Get a line from a file
 * @param fd The file to read
 * @param buffer The buffer to save to. (Probably a char *[])
 * 
*/
int fgets(int fd, char *buffer[], int length){
	return read_object(fd, buffer, length);
}