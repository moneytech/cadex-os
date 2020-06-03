#include "scanf.h"

int scanf(char *line, int length)
{
    int i = 0;
    while (i < (length - 1))
    {
        char c = keyboard_read(0);
        if (c == ASCII_CR)
        {
            line[i] = 0;
            printf("\n");
            return 1;
        }
        else if (c == ASCII_BS)
        {
            if (i > 0)
            {
                putchar(c);
                i--;
            }
        }
        else if (c >= 0x20 && c <= 0x7E)
        {
            putchar(c);
            line[i] = c;
            i++;
        }
    }

    return 0;
}
