/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef STDIO_H
#define STDIO_H

#include <library/syscalls.h>

#define KNO_STDIN  0
#define KNO_STDOUT 1
#define KNO_STDERR 2

void printf_putchar(char c);
#define WN_STDWINDOW 3
void printf_putstring(char *s);
void flush();

void renderWindow(int wd);
void setTextColor(int r, int g, int b);
void drawRect(int x, int y, int w, int h);
void clearScreen(int x, int y, int w, int h);
void drawLine(int x, int y, int w, int h);
void printChar(int x, int y, char c);
void print(int x, int y, char *s);
void flushScreen();
int getWindowDimens(char *s);

#endif
