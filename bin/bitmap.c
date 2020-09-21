#include <stdio.h>

char *SIMPLE_IMAGE =
"..**....**...\n\
 ..**....**...";

#define d(a) printf("%s", a);

void interpret(char *program)
{
    char *ipc = program;
    int x = 0, y = 1;

    while (*ipc)
    {
        if (*ipc == '*')
        {
            setTextColor(WHITE, 0);
            drawRect(x, y, 1, 1);
            flush();
            flushScreen();
            renderWindow(WN_STDWINDOW);
            x++;
        }
        else if (*ipc == '.')
        {
            x++;
        }else if (*ipc=='\n')
        {
            y++;
            x = 0;
        }
        

        *ipc++;
    }
}

int main(int argc, char const *argv[])
{
    int x1 = 12;
    int y1 = 12;

    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];
    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    flush();
    interpret(SIMPLE_IMAGE);
    return 0;
}
