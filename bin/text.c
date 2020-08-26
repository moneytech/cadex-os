#include <stdio.h>
#include <library/scanf.h>

int main(int argc, const char *argv[])
{
    int x1 = 12;
    int y1 = 12;
    int dims[2];
    char stop = -1;
    int i = 0;
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];

    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    flushScreen();
    flush();
    draw_cadex_logo();
    print(70, 35, "Cadex OS");
    drawRect(30, 30, 10, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(30, 30, 20, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(30, 30, 30, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(30, 30, 40, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(30, 30, 50, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    return 0;
}