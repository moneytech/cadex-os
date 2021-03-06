/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "library/stdio.h"
#include "library/string.h"
#include "library/syscalls.h"

/*
    Have a list of programs and windows that we want to run in certain sized
   windows and place them across the screen
*/

#define num_programs 4

typedef struct program {
    int w;
    int h;
    const char *exec;
    const char **args;
    int argc;
} program;

/* Function declarations */
void draw_border(int x, int y, int w, int h, int thickness, int r, int g,
                 int b);
void mergeSort(program *programs, int l, int r);
void merge(program *arr, int l, int m, int r);

int main(int argc, char *argv[]) {
    /* Eventually, programs wont be hardcoded */
    const char *args1[] = {"/usr/bin/snake.exe"};
    const char *args2[] = {"/usr/bin/clock.exe", "08:40"};
    const char *args3[] = {"/bin/cash.exe"};
    const char *args4[] = {"/usr/bin/ball.exe"};
    int window_width = 270;
    int window_height = 270;
    int plot_width = 180;
    int plot_height = 180;
    int thickness = 2;
    int char_offset = 8;
    int r = 255;
    int g = 255;
    int b = 255;
    int x1 = 150;
    int y1 = 150;
    int dx1 = 4;
    int dy1 = 3;
    int dr = -1;
    int dg = 2;

    int padding = 4;
    program programs[] = {
        {.w = 55,
         .h = 25,
         .exec = "/usr/bin/clock.exe",
         .args = args2,
         .argc = 2},
        {.w = 500, .h = 400, .exec = "/bin/cash.exe", .args = args3, .argc = 3},
        {.w = 200,
         .h = 200,
         .exec = "/usr/bin/snake.exe",
         .args = args1,
         .argc = 1},
        {.w = 400,
         .h = 400,
         .exec = "/usr/bin/ball.exe",
         .args = args4,
         .argc = 1}};

    /* Setup the window */
    int std_dims[2];
    syscall_object_size(WN_STDWINDOW, std_dims, 2);
    render_window(WN_STDWINDOW);
    /* The code below will not work */
    clear_screen();
    setTextColor(BLACK, 0);
    set_bg_color(WHITE, 0);
    print(10, 0, "Window Manager");
    resetColor();

    /* Sort programs in order of biggest height to smallest with smaller width
     * being tie breaker */
    int left = 0;
    int right = num_programs - 1;
    mergeSort(programs, left, right);

    /* Packing algorithm - First fit decreasing height - doesnt fit, skip it */
    int spacing = 6;
    int current_pos[num_programs][2] = {
        {0}}; // for each row, keep track of the current x position and height
    int placement[num_programs][3] = {{0}}; // (x, y, valid) of specific program
    int p_i, row;

    for (p_i = 0; p_i < num_programs; ++p_i) {
        for (row = 0; row < num_programs; ++row) {
            if (current_pos[row][0] + programs[p_i].w + 4 * padding <=
                std_dims[0]) {
                // Program can be placed
                // If it is the first element in the row, x == 0
                // And, all of the rows havent been set, set the val of the next
                // row
                if (current_pos[row][0] == 0) {
                    // Probably need to keep track of y coords
                    // If the program overlaps, we cant place it
                    if (current_pos[row][1] + programs[p_i].h + 4 * padding >
                        std_dims[1]) {
                        break;
                    } else if (row < num_programs - 1) {
                        // Otherwise, we can place that element in that row and
                        // we can Set the y position of the next row
                        current_pos[row + 1][1] = current_pos[row][1] +
                                                  spacing + programs[p_i].h +
                                                  4 * padding;
                    }
                }
                // Now, set the placement of this object
                placement[p_i][0] =
                    current_pos[row][0] + 2 * padding; // x coord
                placement[p_i][1] =
                    current_pos[row][1] + 2 * padding; // y coord
                placement[p_i][2] = 1; // program is validly placed
                current_pos[row][0] = current_pos[row][0] + spacing +
                                      programs[p_i].w + 4 * padding;
                ;
                break;
            }
        }
    }

    /* Wrun each program */
    int pids[num_programs] = {0};
    int fds[num_programs][4] = {{0}};
    for (p_i = 0; p_i < num_programs; ++p_i) {
        if (placement[p_i][2] == 0) {
            dbg_printf("[manager.exe] INVALID\n");
            continue;
        }

        fds[p_i][3] = syscall_open_window(WN_STDWINDOW, placement[p_i][0],
                                          placement[p_i][1], programs[p_i].w,
                                          programs[p_i].h);
        fds[p_i][0] = syscall_open_pipe();

        // Standard output and error get console
        fds[p_i][1] = syscall_open_console(fds[p_i][3]);
        fds[p_i][2] = fds[p_i][1];

        // Take in an array of FD's
        pids[p_i] = syscall_process_wrun(programs[p_i].exec, programs[p_i].argc,
                                         programs[p_i].args, fds[p_i], 4);
        render_window(WN_STDWINDOW);
        draw_border(placement[p_i][0] - 2 * padding,
                    placement[p_i][1] - 2 * padding,
                    programs[p_i].w + 4 * padding,
                    programs[p_i].h + 4 * padding, padding, 255, 255, 255);
        flush();
    }

    /* Finally, allow the user to switch between programs*/
    int p_act = 0;
    char tin = 0;

    /* Draw green window around active process and start it */
    render_window(WN_STDWINDOW);
    draw_border(placement[p_act][0] - 2 * padding,
                placement[p_act][1] - 2 * padding,
                programs[p_act].w + 4 * padding,
                programs[p_act].h + 4 * padding, padding, 0, 0, 244);
    flush();

    while (tin != ASCII_ESC) {
        render_window(WN_STDWINDOW);
        draw_border(placement[p_act][0] - 2 * padding,
                    placement[p_act][1] - 2 * padding,
                    programs[p_act].w + 4 * padding,
                    programs[p_act].h + 4 * padding, padding, 0, 0, 244);
        flush();
        if (pids[p_act] == 0) {
            p_act = (p_act + 1) % num_programs;
            continue;
        }

        /* If tab entered, go to the next process */
        read_object(0, &tin, 1);
        if (tin == '\t') {
            render_window(WN_STDWINDOW);
            draw_border(placement[p_act][0] - 2 * padding,
                        placement[p_act][1] - 2 * padding,
                        programs[p_act].w + 4 * padding,
                        programs[p_act].h + 4 * padding, padding, 255, 255,
                        255);
            p_act = (p_act + 1) % num_programs;
            /* Draw green window around active process and start it */
            render_window(WN_STDWINDOW);
            draw_border(placement[p_act][0] - 2 * padding,
                        placement[p_act][1] - 2 * padding,
                        programs[p_act].w + 4 * padding,
                        programs[p_act].h + 4 * padding, padding, 10, 10, 255);
            flush();
            resetColor();
            set_bg_color(WHITE, 0);
            setTextColor(BLACK, 0);
            print(10, 0, "Window Manager");
            resetColor();
            continue;
        }

        /* Write 1 character to the correct pipe */
        syscall_object_write(fds[p_act][0], &tin, 1);
    }

    /* Reap all children processes */
    for (int i = 0; i < num_programs; ++i) {
        syscall_process_reap(pids[i]);
        _process_kill(pids[i]);
        dbg_printf("[manager.exe] killing process %d...", pids[i]);
    }

    /* Clean up the window */
    resetColor();
    clear_screen();
    return 0;
}

/** HELPER FUNCTIONS **/
// Code for mergesort taken from https://www.geeksforgeeks.org/merge-sort/
void mergeSort(program *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(program *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    program L[n1], R[n2];

    for (i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i].h > R[j].h) {
            arr[k] = L[i];
            i++;
        } else if (R[j].h > L[i].h) {
            arr[k] = R[j];
            j++;
        } else if (L[i].w < R[j].w) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void draw_border(int x, int y, int w, int h, int thickness, int r, int g,
                 int b) {
    setTextColor(r, b, g, 0);
    drawRect(x, y, w, thickness);
    drawRect(x, y, thickness, h);
    drawRect(x + w - thickness, y, thickness, h);
    drawRect(x, y + h - thickness, w, thickness);
}
