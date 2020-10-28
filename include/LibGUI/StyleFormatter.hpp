#ifndef _STYLEFORMATTER_HPP_
#define _STYLEFORMATTER_HPP_

#include <iostream>
#include <truegl/truegl.h>

namespace LibGUI {
    class StyleFormatter
    {
    private:
    public:
        StyleFormatter();
        ~StyleFormatter();

        auto Colorize(Colors::Color *color) -> void;
        auto Colorize(int r, int g, int b, int a) -> void;
    };
}

#endif
