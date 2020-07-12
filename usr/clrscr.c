#include <library/stdio.h>
#include <library/color.h>

int main(int argc, char *argv[]){
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];
    clearScreen(width, height, width, height);
    return 0;
}