#include <stdio.h>
#include <truegl/truegl.h>

int main(int argc, char *argv[]) {
    setup_window();
    draw_circle(10, 10, 100);
    getch();
    return 0;
}

