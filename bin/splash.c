/**
 * Fake splash screen for manager.exe
*/

#include <library/scanf.h>
#include <stdio.h>

int main(int argc, const char* argv[])
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
    draw_cadex_logo(130, 20);
    drawRect(80, 80, 10, 10);
    print(85, 100, "Loading components...");
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(80, 80, 20, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    print(85, 100, "Loading /sys/manager.config...");
    sleepThread(1000);
    drawRect(80, 80, 30, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    print(85, 100, "Loading /etc/cash.config...    ");
    sleepThread(1000);
    drawRect(80, 80, 40, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    print(85, 100, "          All set!           ");
    sleepThread(1000);
    drawRect(80, 80, 50, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    drawRect(80, 80, 60, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(80, 80, 70, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(80, 80, 80, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(80, 80, 90, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    drawRect(80, 80, 100, 10);
    renderWindow(WN_STDWINDOW);
    flushScreen();
    flush();
    sleepThread(1000);
    return 0;
}
