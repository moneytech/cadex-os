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
    class GraphicsManager
    {
    private:
        int red, green, blue, alpha;
        int xpos, ypos;

    public:
        GraphicsManager()
        {
        }
        ~GraphicsManager()
        {
        }
        auto draw_line(int x, int y, int width, int height) -> void
        {
            return drawLine(x, y, width, height);
        }
        auto draw_rect(int x, int y, int width, int height) -> void
        {
            return drawRect(x, y, width, height);
        }
        auto set_graphics_context() -> void
        {
        }
        auto set_fgcolor(int r, int g, int b, int a) -> void
        {
            return setTextColor(r, g, b, a);
        }
    };
} // namespace TGL
#endif