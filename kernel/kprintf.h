/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef PRINTF_H
#define PRINTF_H

char getchar();
void putchar(char c);
void kprintf(const char *s, ...);
void dbg_printf(const char *s, ...);
void dbg_print(char *s);
void w_ok_status(char *s);
void w_fail_status(char *s);
#endif
