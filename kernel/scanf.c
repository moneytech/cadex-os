#include <library/errno.h>
#include <library/string.h>
#include <library/objno.h>
#include <library/malloc.h>
#include <library/user-io.h>
#include <kernel/ascii.h>
#include <kernel/types.h>
#include <kernel/syscall.h>
#include <kernel/error.h>
#include <kernel/types.h>
#include "kshell.h"
#include "keyboard.h"
#include "console.h"
#include "string.h"
#include "rtc.h"
#include "kmalloc.h"
#include "page.h"
#include "process.h"
#include "main.h"
#include "fs.h"
#include "syscall_handler.h"
#include "clock.h"
#include "kernelcore.h"
#include "bcache.h"
#include "printf.h"
#include "ata.h"
#include "bitmap.h"

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
