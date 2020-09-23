/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef KERNEL_GFXSTREAM_H
#define KERNEL_GFXSTREAM_H

typedef enum { GRAPHICS_END = 0, GRAPHICS_WINDOW, GRAPHICS_COLOR, GRAPHICS_LINE, GRAPHICS_RECT, GRAPHICS_CLEAR, GRAPHICS_TEXT, GRAPHICS_SCROLLUP, GRAPHICS_BGCOLOR } graphics_command_t;

struct graphics_command {
	graphics_command_t type;
	int args[4];
};

#endif
