/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/**
 * contty.c: Console related functions
 * 
 * This file is a part of the Standard Cadex Library
*/

#include <stdclib.h>
// For syscall_object_size and WN_STDWINDW
#include <stdio.h>

// Store width and height in int array
int dims[2];

/**
 * Get console width
 * @returns int
*/
int get_console_width(){
    // call syscall_object_size and get the object size
    syscall_object_size(WN_STDWINDOW, dims, 2);
    int width = dims[0];
    return width;
}

/**
 * Get the console height
 * @returns int 
*/
int get_console_height(){
    // call syscall_object_size and get the object size
    syscall_object_size(WN_STDWINDOW, dims, 2);
    int height = dims[1];
    return height;
}

/**
 * Sets the console foreground color
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
*/
int set_console_fgcolor(int r, int g, int b, int a){
    setTextColor(r, g, b, a);
    return 0;
}