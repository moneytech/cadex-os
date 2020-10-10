/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * dim: A small text editor designed for Cadex OS
 *
 * NOTE: Because the virtual filesysten is not implemented, you cannot access
 * the cdrom and the hard disk at the same time. Because of that, you cannot
 * access dim.exe when the hard disk is mounted
 */
#include <debug.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <truegl/truegl.h>

/**
 * NOTE: This file is well commented to understand how this works. Use wisely :)
 */
int dims[2];
int i = 0; // Counter 'i'

static void print_line_no(int num) {
    text_color(150, 150, 150); // Set text color to gray
    printf("  %d ", num);      // print the line number
    resetColor();              // set the color to white (default)
}

static void refresh() {
    dbg_printf("[dim.exe] refreshing gui...\n");
    draw_window_border(1, 1, dims[0] - 1, dims[1] - 1, 3, 255, 255, 255);
    set_bg_color(WHITE, 100);
    setTextColor(BLACK, 100);
    print(10, 1, "DiM text editor");
    resetColor();
}

/* A specialised version of scanf() function for DIM */
static int textarea(char *line) {
    int length = 1024;          // Length of string
    int line_number = 1;        // Set the line number to 1
    print_line_no(line_number); // Print the line number
    while (i < (length - 1))    //
    {                           //
        char c;    // C is for storing the character that will be read by
                   // read_object()
        refresh(); // Redraw the window border and title
        read_object(STDIN, &c, 1);      // Read 1 character from the keyboard
        if (c == ASCII_CR)              // Check if 'c' is ENTER
        {                               //
            printf("\n");               // Append a newline
            line_number++;              // Increment the line number value
            print_line_no(line_number); // Print the next line number
            refresh();                  // Redraw the window border and title
        }                               //
        else if (c == ASCII_BS) {
            if (i > 0) {
                printf("%c", c);
                i--;
            }
        } else if (c == ASCII_ESC) {
            printf("\n  > ");
            char command[1024];
            refresh();
            scanf(command, sizeof(command));

            if (!strcmp(command, ":q")) {
            ask_save_file:
                printf("\n   Save file to disk? (Enter=OK, ESC=Cancel) ");
                refresh();
                char keystroke;
                read_object(STDIN, &keystroke, 1);
                if (keystroke == ASCII_CR) {
                    refresh();
                    read_object(STDIN, 0, 1);
                    break;
                } else if (keystroke == ASCII_ESC) {
                    break;
                } else {
                    refresh();
                    goto ask_save_file;
                }
            } else {
                setTextColor(CLEAR_RED, 0);
                printf("  Invalid command: %s\n", command);
                dbg_printf("[dim.exe] invalid command '%s'\n", command);
                resetColor();
                // print_line_no(line_number);
                continue;
            }
        } else if (c >= 0x20 && c <= 0x7E) {
            printf_putchar(c);
            line[i] = c;
            i++;
            refresh();
        }
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    dbg_printf("[dim.exe] DiM version 0.1.2\n");
    syscall_object_size(WN_STDWINDOW, dims, 2);
    char *input[2048];
    setup_window();
    clear_screen();
    printf("\n\n");
    dbg_printf("[dim.exe] textarea() started\n");
    textarea(&input);
    dbg_printf("[dim.exe] exiting DiM\n");
    clear_screen();
    return 0;
}
