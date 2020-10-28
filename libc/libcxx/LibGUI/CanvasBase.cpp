#include <LibGUI/CanvasBase.hpp>

LibGUI::CanvasBase::CanvasBase() {}

LibGUI::CanvasBase::~CanvasBase() {}

auto DrawRect(int x, int y, int w, int h) -> void { drawRect(x, y, w, h); };

auto DrawLine(int x, int y, int w, int h) -> void { drawLine(x, y, w, h); };

auto DrawPixel(int x, int y) -> void { drawRect(x, y, 1, 1); };
