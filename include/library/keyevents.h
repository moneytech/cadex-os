#include <library/stdio.h>
#include <library/stdbool.h>

typedef struct event
{
    int eventid;
    int eventType;
    char *eventname;
};

typedef struct keyEventHandler
{
    event keydown;
    event keyup;
    event keypress;
    event afterKeyDown;
    event afterKeyPress;
    event afterKeyUp;
};
