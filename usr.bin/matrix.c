#include <library/scanf.h>
#include <stdio.h>

int main(int argc, const char* argv[])
{
    int rows, cols, i, j, k;
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);
    int height = dims[1];
    cols = 128;
    rows = height;
    renderWindow(WN_STDWINDOW);
    clear_screen();
    k = 1;
    while (1) {
        for (i = 1; i <= rows; i++) {
            for (j = 1; j <= cols; j++) {
                if (k == 1) {
                    renderWindow(WN_STDWINDOW);
                    setTextColor(10, 200, 10, 100);
                    printf("1 ");
                } else {
                    setTextColor(10, 100, 10, 100);
                    printf("0 ");
                }
                k *= -1;
            }
            if (cols % 2 == 0) {
                k *= -1;
            }
            sleepThread(200);
            //printf("\n");
        }
    }

    //return 0;
}
