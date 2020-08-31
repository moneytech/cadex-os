/**
 * TrueGL Graphics Library v0.2
 * 
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <truegl/truegl.h>

extern int movable_scanf(int x, int y, char *line, int length)
{
    int i = 0;
    char c;
    while (1)
    {
        syscall_object_read(0, &c, 1);
        if (c == ASCII_CR)
        {
            print(x, y, c);
            flushScreen();
            flush();
            line[i] = 0;
            return i;
        }
        else if (c == ASCII_BS)
        {
            if (i > 0)
            {
                i--;
                print(x, y, c);
                flushScreen();
                flush();
            }
        }
        else
        {
            if (i < (length - 1))
            {
                line[i] = c;
                i++;
                print(x, y, c);
                flushScreen();
                flush();
            }
        }
    }
}