/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * Console-related I/O functions
*/
#ifndef _CONIO_H
#define _CONIO_H

#include <stdio.h>

//! contty.c
/**
 * Get the console width
 * @return int
*/
int get_console_width();
/**
 * Get the console height
 * @return int
*/
int get_console_height();
#endif // !CONTTY