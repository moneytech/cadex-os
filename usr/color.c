/*
Simple application to change color of text.
*/
#include <library/stdio.h>
#include <library/string.h>
#include <library/types.h>
#include <library/color.h>

int main(int argc, char *argv[])
{
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];
    renderWindow(WN_STDWINDOW);
    // clearScreen(0, 0, width, height);
    if (!strcmp(argv[0], "blue")) {
        setTextColor(BLUE,0);
    }
    else {
        printf("Usage: color.exe <color>");
    }
    flush();
    return 0;
}