/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "kernel/gfxstream.h"
#include "kernel/types.h"
#include "library/user-io.h"
#include "library/syscalls.h"
#include "library/string.h"
#include "stdarg.h"

static char stdio_buffer[PAGE_SIZE] = { 0 };

static uint32_t stdio_buffer_index = 0;

static struct graphics_command graphics_buffer[PAGE_SIZE] = { {0} };

static uint32_t graphics_buffer_index = 0;

static int window_fd = KNO_STDWIN;

void flush()
{
	syscall_object_write(KNO_STDOUT, stdio_buffer, stdio_buffer_index);
	stdio_buffer_index = 0;
	stdio_buffer[0] = 0;
}

static void printf_buffer(char *s, unsigned len)
{
	while(len) {
		unsigned l = len % (PAGE_SIZE - 1);
		if(l > PAGE_SIZE - stdio_buffer_index - 1) {
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
	if(c == '\n')
		flush();
}

void printf_putstring(char *s)
{
	printf_buffer(s, strlen(s));
}

static void draw_set_buffer(int t, int a0, int a1, int a2, int a3)
{
	struct graphics_command c = { t, {a0, a1, a2, a3} };
	graphics_buffer[graphics_buffer_index++] = c;
}

void draw_flush()
{
	draw_set_buffer(GRAPHICS_END, 0, 0, 0, 0);
	syscall_object_write(window_fd, graphics_buffer, graphics_buffer_index);
	graphics_buffer_index = 0;
}

void draw_window(int wd)
{
	window_fd = wd;
}

void draw_color(int r, int g, int b)
{
	draw_set_buffer(GRAPHICS_COLOR, r, g, b, 0);
}

void draw_rect(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_RECT, x, y, w, h);
}

void draw_clear(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_CLEAR, x, y, w, h);
}

void draw_line(int x, int y, int w, int h)
{
	draw_set_buffer(GRAPHICS_LINE, x, y, w, h);
}

void draw_string(int x, int y, char *s)
{
	draw_set_buffer(GRAPHICS_TEXT, x, y, (int) s, 0);
}
uint8_t inb(uint16_t port)
{
	uint8_t data;
	asm volatile("inb %1, %0"
				 : "=a"(data)
				 : "Nd"(port));
	return data;
}

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
// A simple beep implementation. See https://wiki.osdev.org/PC_Speaker#Sample_Code/ /**Code by HyperCreeck**/
void sleep(uint32_t timer_count)
{
	wait_for_io(timer_count * 0x02FFFFFF);
}
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

//make it shutup
static void nosound()
{
	uint8_t tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}

//Make a beep
void beep()
{
	play_sound(1000);
	sleep(10);
	nosound();
	//set_PIT_2(old_frequency);
}
// End sound code

