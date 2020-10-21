#ifndef _GLX_H
#define _GLX_H

#include <stdio.h>
#include <truegl/events.h>
#include <truegl/keyevents.h>

typedef struct twindow {
    union properties {
        int x;
        int y;
        int width;
        int height;
        int top_level_window;
        int visibility;
    } * properties;

} twindow_t;

extern twindow_t root_window;
#endif
