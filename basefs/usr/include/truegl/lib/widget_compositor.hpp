#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <truegl/lib/graphics.hpp>
#include <truegl/lib/widget.hpp>

namespace TGL::Core {
class WCompositor {
private:
    int wa, ha, xa, ya, bt, ra, ga, ba;

public:
    WCompositor();
    ~WCompositor();
    auto draw_window(int w, int h, int padding, int border_thickness) -> void
    {
        draw_window_border(0 + padding, 0 + padding, w - padding, h - padding, border_thickness, 255, 255, 255);
    }
};
} // namespace TGL::Core

#endif
