/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "library/syscalls.h"
#include "library/string.h"
#include "library/stdio.h"
#include "kernel/types.h"

/*
	Display time in a window
*/

/* Function declarations */
void draw_border(int x, int y, int w, int h, int thickness, int r, int g, int b);
void draw_clock(uint32_t hour, uint32_t minute, int timezone, int military, int x, int y, int padding, int r, int g, int b);

int main(int argc, char *argv[])
{
	/* Configure clock params */
	int military = 0;
	if (argc > 1 && strcmp(argv[1], "military") == 0)
	{
		military = 1;
	}
	int timezone = 5;

	/* Get initial time */
	struct rtc_time time;
	syscall_system_rtc(&time);

	/* Clock draw params */
	int CLOCK_W = 55;
	int CLOCK_H = 25;
	int thickness = 4;
	int dims[2];
	syscall_object_size(WN_STDWINDOW, dims, 2);

	int width = dims[0];
	int height = dims[1];

	/* Set up window  */
	renderWindow(WN_STDWINDOW);
	clearScreen(0, 0, width, height);
	draw_border(0, 0, CLOCK_W, CLOCK_H, thickness, 255, 255, 255);
	draw_clock(time.hour, time.minute, timezone, military, 0, 0, 2 * thickness, 255, 255, 255);
	flush();

	/* Run Clock */
	char c = 0;
	while (c != 'q')
	{
		syscall_object_read_nonblock(0, &c, 1);
		sleepThread(2000);
		syscall_system_rtc(&time);
		draw_clock(time.hour, time.minute, timezone, military, 0, 0, 2 * thickness, 255, 255, 255);
		flush();
	}

	return 0;
}

void draw_border(int x, int y, int w, int h, int thickness, int r, int g, int b)
{
	setTextColor(r, b, g);
	drawRect(x, y, w, thickness);
	drawRect(x, y, thickness, h);
	drawRect(x + w - thickness, y, thickness, h);
	drawRect(x, y + h - thickness, w, thickness);
}

void draw_clock(uint32_t hour, uint32_t minute, int timezone, int military, int x, int y, int padding, int r, int g, int b)
{
	setTextColor(r, b, g);

	char h_str[100];
	char m_str[100];
	char time[100] = "";

	/* Configure time */
	int tz_hour = (int)hour - timezone;
	if (tz_hour < 0)
	{
		tz_hour += 24;
	}

	if (military == 0 && tz_hour > 12)
	{
		tz_hour -= 12;
	}

	uint_to_string((uint32_t)tz_hour, h_str);
	uint_to_string(minute, m_str);

	/* Format time string */
	if (strlen(h_str) == 1)
	{
		strcat(time, " ");
	}
	strcat(time, (const char *)h_str);
	strcat(time, ":");
	if (strlen(m_str) == 1)
	{
		strcat(time, "0");
	}
	strcat(time, (const char *)m_str);

	print(x + padding, y + padding, time);
}
