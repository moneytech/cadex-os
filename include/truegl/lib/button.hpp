#ifndef _TBUTTON_HPP
#define _TBUTTON_HPP

#include <truegl/lib/widget_compositor.hpp>

namespace TGL
{
    class TButton : public TWidget
    {
    private:
        int x = 0;
        int y = 0;
        int width = 100;
        int height = 100;
        char *tmlabel = 0;
        std::String *tmstr;

    public:
        TButton();
        TButton(std::String title);
        TButton(char *title)
        {
            GraphicsManager::draw_rect(x, y, width + strlen(title) + 10, height);
            GraphicsManager::draw_string(x + width / 2, y + height / 2, title);
        }
        ~TButton();
    };
} // namespace TGL
#endif // !_TBUTTON_HPP