/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * Mouse driver for userspace apps and libraries
*/
#ifndef MOUSE_H
#define MOUSE_H

#include <library/types.h>

// Mouse event; Use this struct to access the mouse properties
struct mouse_event
{
	uint8_t buttons;
	int32_t x;
	int32_t y;
};

typedef enum mouse_button
{
	M_BUTTON_LEFT,
	M_BUTTON_MIDDLE,
	M_BUTTON_RIGHT
} mouse_button_t;

uint8_t ps2_read_data();
void ps2_write_data(uint8_t data);
void ps2_write_command(uint8_t data);
void ps2_clear_buffer();
void ps2_mouse_command(uint8_t command);
static void mouse_interrupt(int i, int code);
void mouse_read(struct mouse_event *e);
//void mouse_init();
#endif
