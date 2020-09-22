#include <stdio.h>
#include <unistd.h>
#include <library/mouse.h>
#include <library/syscalls.h>

int x, y;
struct mouse_event *m;
int a = -1;

int main(int argc, const char *argv[])
{
    renderWindow(WN_STDWINDOW);
    drawRect(10, 10, 100, 100);
    while (1)
    {
        dev_mouse_read(&m);
        // if (m.x < 1024 && m.y < 768)
            // printf("x=%d, y=%d\n", m.x, m.y);
        if(m->buttons > 0){
            printf("m.button=%d\n", m->buttons);
        }
    }
    return 0;
}