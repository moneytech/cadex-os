#ifndef _CANVASBASE_HPP_
#define _CANVASBASE_HPP_

#include <LibGUI/GUIBase.hpp>

namespace LibGUI {
class CanvasBase {
    private:
    public:
    CanvasBase(/* args */);
    ~CanvasBase();

    auto DrawRect(int x, int y, int w, int h) -> void;
    auto DrawLine(int x, int y, int w, int h) -> void;
    auto DrawPixel(int x, int y) -> void;
};
} // namespace LibGUI
#endif // !_CANVASBASE_HPP_
