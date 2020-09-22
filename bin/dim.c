/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

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

/**
 * NOTE: This file is well commented to understand how this works. Use wisely :)
*/
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
        draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
        print(10, 1, "Dim text editor");
        read_object(0, &c, 1);
        if (c == ASCII_CR)
        {
            //line[i] = 0;
            printf("\n");
            x++;
            printf("  %d ", x);
            draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
            print(10, 1, "Dim text editor");
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
            print(10, 1, "Dim text editor");
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
            print(10, 1, "Dim text editor");
        }
    }

    return 0;
}

int main(int argc, const char *argv[]) // Main function
{
    int width = dims[0];                                                  // Variable declaration
    int height = dims[1];                                                 // Variable declaration
    syscall_object_size(WN_STDWINDOW, dims, 2);                           // Get the dimensions of the window; Likely to be removed in version 0.1.8
    char *line[1024];                                                     // Declare the variable to which we will save the text data
    renderWindow(WN_STDWINDOW);                                           // Render the window
    clear_screen();                                                       // clear the screen; We are using clear_screen() which prints out '\f' which clears the screen
    draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255); // Draw te border
    print(10, 1, "Dim text editor");                                      // Print the title to the console
    printf("\n\n");                                                       // Append two newlines to move the editor part down
    textarea(line, sizeof(line));                                         // And now its time to start the editor part
    clear_screen();                                                       // Clear the screen before exiting
    return 0;                                                             // Return 0
}