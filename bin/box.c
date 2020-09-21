#include <stdio.h>
#include <library/scanf.h>

int a;

int main(int argc, const char *argv[])
{
    printf("Box: A simple but mind blowing game\n"); // just an intro :)
    renderWindow(WN_STDWINDOW);
    while (1)
    {
        read_object(0, a, 1);
        if (a == ASCII_w)
        {
            drawRect(10, 10, 100, 100);
        }
        else
        {
            break;
        }
    }
    return 0;
}