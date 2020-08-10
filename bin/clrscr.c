#include <library/stdio.h>
#include <library/color.h>

int main(int argc, char *argv[]){
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
    flush();
    return 0;
}