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

void refresh()
{
    draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
    set_bg_color(WHITE, 0);
    setTextColor(BLACK, 0);
    print(10, 1, "DiM text editor");
    resetColor();
}
/* A specialised version of scanf() function for DIM */
int textarea(char *line, int length)
{
    int i = 0;                            // Counter 'i'
    int line_number = 1;                  // Set the line number to 1
    printf("  %d ", line_number);         // Print the line number
    while (i < (length - 1))              //
    {                                     //
        char c;                           // C is for storing the character that will be read by read_object()
        refresh();                        // Redraw the window border and title
        read_object(STDIN, &c, 1);        // Read 1 character from the keyboard
        if (c == ASCII_CR)                // Check if 'c' is ENTER
        {                                 //
            printf("\n");                 // Append a newline
            line_number++;                // Increment the line number value
            printf("  %d ", line_number); // Print the next line number
            refresh();                    // Redraw the window border and title
        }                                 //
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
            printf("\n  > ");
            char command[1024];
            refresh();
            scanf(command, sizeof(command));

            if (!strcmp(command, ":q"))
            {
            ask:
                printf("\n  Do you want to copy the text that you typed to the memory? (Enter=OK, ESC=Cancel) ");
                refresh();
                char as;
                read_object(STDIN, &as, 1);
                if (as == ASCII_CR)
                {
                    printf("\n  Text copied to the memory. Access it using the 'getmemtxt' command. Press any key to continue...");
                    refresh();
                    read_object(STDIN, 0, 1);
                    break;
                }
                else if (as == ASCII_ESC)
                {
                    break;
                }
                else
                {
                    refresh();
                    goto ask;
                }
            }
            else
            {
                setTextColor(CLEAR_RED, 0);
                printf("  Invalid command: %s\n", command);
                resetColor();
                printf("  %d ", line_number);
                continue;
            }
        }
        else if (c >= 0x20 && c <= 0x7E)
        {
            printf_putchar(c);
            line[i] = c;
            i++;
            refresh();
        }
    }

    return 0;
}

int main(int argc, const char *argv[]) // Main function
{
    syscall_object_size(WN_STDWINDOW, dims, 2); // Get the dimensions of the window; Likely to be removed in version 0.1.8
    char *input[2048];                          // Declare the variable to which we will save the text data
    renderWindow(WN_STDWINDOW);                 // Render the window
    clear_screen();                             // clear the screen; We are using clear_screen() which prints out '\f' which clears the screen
    printf("\n\n");                             // Append two newlines to move the editor part down
    textarea(&input, sizeof(input));            // And now its time to start the editor part
    clear_screen();                             // Clear the screen before exiting
    return 0;                                   // Return 0
}
