/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/
#include <library/scanf.h>
#include <stdio.h>

#define SCANF_KBD_PORT   0x03B
#define SCANF_STDLIB_VER 0x00B

int scanf(char *line, int length) {
    int i = 0;
    while (i < (length - 1)) {
        char c;
        read_object(0, &c, 1);
        if (c == ASCII_CR) {
            line[i] = 0;
            printf("\n");
            return 1;
        } else if (c == ASCII_BS) {
            if (i > 0) {
                printf_putchar(c);
                i--;
            }
        } else if (c >= 0x20 && c <= 0x7E) {
            printf_putchar(c);
            line[i] = c;
            i++;
        }
    }

    return 0;
}

// extern int scanf(char *line, int length)
// {
//     int i = 0;
//     char c;
//     while (1)
//     {
//         read_object(0, &c, 1);
//         if (c == ASCII_CR)
//         {
//             printf_putchar(c);
//             flushScreen();
//             flush();
//             line[i] = 0;
//             return i;
//         }
//         else if (c == ASCII_BS)
//         {
//             if (i > 0)
//             {
//                 i--;
//                 printf_putchar(c);
//                 flushScreen();
//                 flush();
//             }
//         }
//         else
//         {
//             if (i < (length - 1))
//             {
//                 line[i] = c;
//                 i++;
//                 printf_putchar(c);
//                 flushScreen();
//                 flush();
//             }
//         }
//     }
// }
extern int passwd_scanf(char *line, int length) {
    int i = 0;
    char c;
    while (1) {
        read_object(0, &c, 1);
        if (c == ASCII_CR) {
            // printf_putchar(c);
            flushScreen();
            flush();
            line[i] = 0;
            return i;
        } else if (c == ASCII_BS) {
            if (i > 0) {
                i--;
                // printf_putchar(c);
                flushScreen();
                flush();
            }
        } else {
            if (i < (length - 1)) {
                line[i] = c;
                i++;
                // printf_putchar(c);
                flushScreen();
                flush();
            }
        }
    }
}
