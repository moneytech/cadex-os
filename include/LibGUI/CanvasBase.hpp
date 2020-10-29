#ifndef _CANVASBASE_HPP_
#define _CANVASBASE_HPP_

#include <LibGUI/GUIBase.hpp>

namespace LibGUI {
class CanvasBase {
private:
    /* Private variables for internal functions */
    int xpos;
    int ypos;
    int width;
    int height;
    bool visible;

public:
    /* Constructor and destructor */
    CanvasBase();
    ~CanvasBase();

    /* Virtual functions */
    virtual void on_draw() = 0;
    virtual void on_draw_finish() = 0;
    virtual void on_create() = 0;
};
} // namespace LibGUI
#endif // !_CANVASBASE_HPP_
