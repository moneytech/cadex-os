typedef enum mouse_button
{
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT
}mouse_button_t;

typedef struct{
    int mouse_down;
    mouse_button_t mouse_button;
    union
    {
        int x;
        int y;
        int w;
        int h;
        char *label;
    }*props;
    
} tgl_event_t;
