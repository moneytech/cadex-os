/**
 * dim: A small text editor designed for Cadex OS
 * 
 * NOTE: Because the virtual filesysten is not implemented, you cannot access
 * the cdrom and the hard disk at the same time. Because of that, you cannot access
 * dim.exe when the hard disk is mounted
*/
#include <stdio.h>
#include <library/scanf.h>
#include <truegl/truegl.h>

int main(int argc, const char *argv[])
{
    int r = 255;
    int g = 0;
    int b = 0;
    int x1 = 12;
    int y1 = 12;
    int dx1 = 4;
    int dy1 = 1;
    int dr = -1;
    int dg = 2;
    int db = 3;

    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];
    char *line[1024];
    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    draw_window_border(1, 1, width - 1, height - 1, 3, 255, 255, 255);
    print(10, 10, "*Untitled - dim");
    setTextColor(WHITE, 0);
    drawRect(0, 22, width, 3);
    setTextColor(GREEN, 0);
    printf("    1 ");
    scanf(line, sizeof(line));
    //gui_set_bgcolor(GREEN, 100);
    return 0;
}