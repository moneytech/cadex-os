#include <LibGUI/StyleFormatter.hpp>

LibGUI::StyleFormatter::StyleFormatter() {}

LibGUI::StyleFormatter::~StyleFormatter() {}

auto LibGUI::StyleFormatter::Colorize(Colors::Color *color) -> void {
    setTextColor(color->r, color->g, color->b, color->a);
};

auto LibGUI::StyleFormatter::Colorize(int r, int g, int b, int a) -> void {
    setTextColor(r, g, b, a);
};
