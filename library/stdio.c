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
static char stdio_buffer[PAGE_SIZE] = { 0 };

static uint32_t stdio_buffer_index = 0;

static struct graphics_command graphics_buffer[PAGE_SIZE] = { {0} };

static uint32_t graphics_buffer_index = 0;
 
static int window_fd = WN_STDWINDOW;

void flushScreen()      
{
	syscall_object_write(KNO_STDOUT, stdio_buffer, stdio_buffer_index);
	stdio_buffer_index = 0;
	stdio_buffer[0] = 0;
}

static void draw_set_buffer(int t, int a0, int a1, int a2, int a3)
{
	struct graphics_command c = { t, {a0, a1, a2, a3} };
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
}

// Sets the text/cursor color
void setTextColor(int r, int g, int b)
{
	draw_set_buffer(GRAPHICS_COLOR, r, g, b, 0);
	flushScreen();
}

// Draws a rectangle on screen with specified dimensions
void drawRect(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
	flushScreen();
}

// Clears the screen
void clearScreen(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_CLEAR, x, y, w, h);
	flushScreen();
}
// Draws a line on screen on the specified x and y axis with the specified width and height.
void drawLine(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_LINE, x, y, w, h);
	flushScreen();
}

// Prints text on screen on the specified x and y axis.
void print(int x, int y, char *s)
{
	draw_set_buffer(GRAPHICS_TEXT, x, y, (int) s, 0);
	flushScreen();
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
int getWindowDimens(char *type){
	int dims[2];
	syscall_object_size(WN_STDWINDOW, dims, 2);

	int width = dims[0];
	int height = dims[1];
	if(!strcmp(type[0], "width")){
		return width;
	}
	if(!strcmp(type[0], "height")){
		return height;
	}
	return width, height;
}

// Executes specified file with specified argc and argv. 
void system(char *program, int argc, char **argv) {
	syscall_process_exec(program, argc, argv);
}
