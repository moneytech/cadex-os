/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef MOUSE_H
#define MOUSE_H

#include <library/types.h>

struct mouse_event {
	uint8_t buttons;
	int32_t x;
	int32_t y;
};

//void mouse_read(struct mouse_event *e);
//void mouse_init();
uint8_t ps2_read_data();
void ps2_write_data(uint8_t data);
void ps2_write_command(uint8_t data);
void ps2_clear_buffer();
void ps2_mouse_command(uint8_t command);
static void mouse_interrupt(int i, int code);
void mouse_read(struct mouse_event *e);
//void mouse_init();
#endif
