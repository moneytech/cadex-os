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

int dims[2];

/* A specialised version of scanf() function for DIM */
int textarea(char *line, int length)
{
    int i = 0;
    int x = 1;
    printf("  %d ", x);
    while (i < (length - 1))
    {
        char c;
        read_object(0, &c, 1);
        if (c == ASCII_CR)
        {
            //line[i] = 0;
            printf("\n");
            x++;
            printf("  %d ", x);
            draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
        }
        // else if (c == ASCII_BACKTICK)
        // {
        //     line[i] = 0;
        //     syscall_object_size(WN_STDWINDOW, dims, 2);
        //     renderWindow(WN_STDWINDOW);
        //     clearScreen(0, 0, dims[0], dims[1]);
        //     printf("\n");
        //     return 1;
        // }

        else if (c == ASCII_BS)
        {
            if (i > 0)
            {
                printf("%c", c);
                i--;
            }
        }
        else if (c == ASCII_ESC)
        {
            printf("\n  -> ");
            char command[1024];
            draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
            scanf(command, sizeof(command));

            if (!strcmp(command, ":q"))
            {
                break;
            }
            else
            {
                printf("invalid command: %s\n", command);
                printf("  %d ", x);
                continue;
            }
        }
        else if (c >= 0x20 && c <= 0x7E)
        {
            printf_putchar(c);
            line[i] = c;
            i++;
            draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
        }
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    int width = dims[0];
    int height = dims[1];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    char *line[1024];
    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, dims[0], dims[1]);
    draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
    printf("Dim text editor\n");
    textarea(line, sizeof(line));
    return 0;
}