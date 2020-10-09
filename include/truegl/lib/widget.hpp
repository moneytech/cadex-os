/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#ifndef _TRUEGL_WIDGET
#define _TRUEGL_WIDGET

#include <stdio.h>
#include <string>

namespace TGL {
class WidgetBase {
public:
    WidgetBase() { }
    WidgetBase(WidgetBase&&) { }
    ~WidgetBase() { }

private:
};

class TWidget : public WidgetBase {
private:
    int height;
    int width;
    int x;
    int y;
    char* label;

public:
    TWidget()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        label = "";
    }
    ~TWidget()
    {
        free(label);
    }
};

} // namespace TGL
#endif // !_TRUEGL_WIDGET
