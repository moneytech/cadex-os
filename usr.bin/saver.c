/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/*
A fun graphics demo that features a line segment bouncing around the screen.
*/

#include "library/stdio.h"
#include "library/string.h"
#include "library/syscalls.h"

typedef unsigned int uint32_t;

uint32_t randint(uint32_t min, uint32_t max);
void move(int* x, int* d, int min, int max);

int main(int argc, char* argv[])
{
    int r = 255;
    int g = 0;
    int b = 0;
    int x1 = 12;
    int y1 = 12;
    int x2 = 48;
    int y2 = 48;
    int dx1 = 4;
    int dy1 = 1;
    int dx2 = -2;
    int dy2 = -2;
    int dr = -1;
    int dg = 2;
    int db = 3;

    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];

    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    flush();

    char stop = -1;
    while (stop == -1) {
        move(&x1, &dx1, 0, width - 1);
        move(&y1, &dy1, 0, height - 1);
        move(&x2, &dx2, 0, width - 1);
        move(&y2, &dy2, 0, height - 1);
        move(&r, &dr, 0, 255);
        move(&g, &dg, 0, 255);
        move(&b, &db, 0, 255);
        renderWindow(WN_STDWINDOW);
        setTextColor(r, g, b, 0);

        drawLine(x1, y1, x2 - x1, y2 - y1);
        flush();
        sleepThread(1);
        read_object_nonblock(KNO_STDIN, &stop, 1);
    }
    clearScreen(0, 0, width, height);
    setTextColor(255, 255, 255, 0);
    flush();
    return 0;
}

uint32_t randint(uint32_t min, uint32_t max)
{
    static uint32_t state = 0xF3DC1A24;
    state = (state * 1299721) + 29443;
    return min + ((state >> 16) % (max - min + 1));
}

void move(int* x, int* d, int min, int max)
{
    *x += *d;
    if (*x < min) {
        *x = min;
        *d = randint(1, 10);
    }
    if (*x > max) {
        *x = max;
        *d = -randint(1, 10);
    }
}
