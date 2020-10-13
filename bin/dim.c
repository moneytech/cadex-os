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
#include <string.h>
#include <truegl/truegl.h>
#include <unistd.h>

/**
 * NOTE: This file is well commented to understand how this works. Use wisely :)
 */
int dims[2];
int i = 0; // Counter 'i'

bool verbose = 0;

static void dim_open_script(char *script) {
    int file = syscall_open_file("/usr/share/", 0, 0);
    if (file > 0) {
        // TODO: Read the contents of the file and pass it to lexer
    } else {
        printf("error reading %s: %s", script, strerror(file));
    }
}

static void print_line_no(int num) {
    text_color(150, 150, 150); // Set text color to gray
    printf("  %d ", num);      // print the line number
    if (verbose)
        dbg_printf("[dim.exe] printing line no %d...", num);
    resetColor(); // set the color to white (default)
}

static void refresh() {
    if (verbose)
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
        read_object(STDIN, &c, 1); // Read 1 character from the keyboard

        /* Check if 'c' is '\n' (ENTER) */
        if (c == ASCII_CR) {
            /* Append a newline */
            printf("\n");
            /* Increment the line number value */
            line_number++;
            /* Print the next line number */
            print_line_no(line_number);
            /* Redraw the window border and title */
            refresh();
        }
        /* Check if 'c' is '\b' (BACKSPACE) */
        else if (c == ASCII_BS) {
            if (i > 0) {
                printf("%c", c);
                i--;
            }
        }
        /* Check if 'c' is ESCAPE */
        else if (c == ASCII_ESC) {
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
                print_line_no(line_number);
                continue;
            }
        }
        /* Check if 'c'' is A-z or 0-9 */
        else if (c >= 0x20 && c <= 0x7E) {
            printf_putchar(c);
            line[i] = c;
            i++;
            refresh();
        }
        /* Check if 'c' is ^C (CTRL + C) */
        else if (c == 0x03) {
            dbg_printf("[dim.exe] ^C pressed: Terminating process...\n");
            /* Clear screen before exiting */
            clear_screen();
            printf("\n^C");

            /* Terminate the process */
            exit(0);
        }
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    dbg_printf("[dim.exe] DiM version 0.1.2\n");

    if (argc > 0) {
        if (!strcmp(argv[0], "-v") || !strcmp(argv[0], "--verbose")) {
            /* Set verbose to true */
            verbose = true;
        } else {
            /* Set verbose to false */
            verbose = false;
        }
    }

    /* Init */
    syscall_object_size(WN_STDWINDOW, dims, 2);
    char *input[2048];
    setup_window();
    clear_screen();
    printf("\n\n");

    /* Load editor */
    dbg_printf("[dim.exe] textarea() started\n");
    textarea(&input);
    dbg_printf("[dim.exe] exiting DiM\n");

    /* Clear screen before exiting */
    clear_screen();
    return 0;
}
