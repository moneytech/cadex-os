#ifndef _CANVAS_HPP_
#define _CANVAS_HPP_

#include <LibGUI/CanvasBase.hpp>

namespace LibGUI {
class Canvas : public CanvasBase {
private:
    int x;
    int y;
    int width;
    int height;

public:
    /* Constructor and destructor */
    Canvas(int x, int y, int width, int height);
    ~Canvas();

    /* Virtual functions */
    virtual void on_draw() override;
    virtual void on_draw_finish() override;
    virtual void on_create() override;

    /* Helper functions */
    auto draw_rect(int x, int y, int w, int h) -> void;
    auto draw_line(int x, int y, int w, int h) -> void;
    auto draw_pixel(int x, int y) -> void;
};
}
#endif
