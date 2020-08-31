#include <stdio.h>
#include <library/scanf.h>
#include <library/mouse.h>

int main(int argc, const char *argv[])
{
    struct mouse_event *e;
    while (1)
    {
        mouse_read(e);
        print(e->x, e->y, "hello");
    }
    
    return 0;
}