/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * Graphics-related header-only class definitions for TrueGL
*/
#ifndef _TRUEGL_GRAPHICS
#define _TRUEGL_GRAPHICS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <__config>

namespace TGL
{
    class GraphicsContext
    {
    private:
        /* data */
    public:
        GraphicsContext(/* args */);
        ~GraphicsContext();
    };

    class GraphicsManager
    {
    private:
        int red, green, blue, alpha;
        int xpos, ypos;
        static GraphicsContext current_context;

    public:
        GraphicsManager()
        {
        }
        ~GraphicsManager()
        {
        }
        static auto draw_line(int x, int y, int width, int height) -> void
        {
            return drawLine(x, y, width, height);
        }
        static auto draw_rect(int x, int y, int width, int height) -> void
        {
            return drawRect(x, y, width, height);
        }
        static auto draw_string(int x, int y, char *str) -> void
        {
            return print(x, y, str);
        }
        static auto set_graphics_context(GraphicsContext ctx) -> void
        {
            current_context = ctx;
        }
        static auto set_fgcolor(int r, int g, int b, int a) -> void
        {
            return setTextColor(r, g, b, a);
        }
        static auto set_bgcolor(int r, int g, int b, int a) -> void
        {
            return set_bg_color(r, g, b, a);
        }

        /* Properties */
        static int is_window_created;
        static int window_title;
    };
} // namespace TGL
#endif