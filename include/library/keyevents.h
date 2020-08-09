#include <library/stdio.h>
#include <library/stdbool.h>

typedef struct {
    int eventid;
    int eventType;
    char *eventname;
}event;

typedef struct keyEventHandler
{
    event keydown;
    event keyup;
    event keypress;
    event afterKeyDown;
    event afterKeyPress;
    event afterKeyUp;
};
enum key_event_codes
{
    E_KEY_PRESS,
    E_KEY_DOWN,
    E_KEY_UP,
    E_AFTER_KEYPRESS,
    E_AFTER_KEYDOWN,
    E_AFTER_KEYUP
};
