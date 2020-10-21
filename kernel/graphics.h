/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "kernel/gfxstream.h"
#include "kernel/types.h"

struct graphics_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

extern struct graphics graphics_root;
static int console_blinking = 1;

struct graphics *graphics_create_root();
struct graphics *graphics_create(struct graphics *parent);
struct graphics *graphics_addref(struct graphics *g);
void graphics_delete(struct graphics *g);

uint32_t graphics_width(struct graphics *g);
uint32_t graphics_height(struct graphics *g);
void graphics_fgcolor(struct graphics *g, struct graphics_color c);
void graphics_bgcolor(struct graphics *g, struct graphics_color c);
void graphics_set_fgcolor(int r, int g, int b, int a);
int graphics_clip(struct graphics *g, int x, int y, int w, int h);

void graphics_scrollup(struct graphics *g, int x, int y, int w, int h, int dy);
void graphics_rect(struct graphics *g, int x, int y, int w, int h);
void graphics_clear(struct graphics *g, int x, int y, int w, int h);
void graphics_line(struct graphics *g, int x, int y, int w, int h);
void graphics_char(struct graphics *g, int x, int y, unsigned char c);
void graphics_bitmap(struct graphics *g, int x, int y, int width, int height,
                     uint8_t *data);
int graphics_write(struct graphics *g, struct graphics_command *command);

#endif
