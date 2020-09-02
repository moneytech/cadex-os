/**
 * Cadex CBasic
 * (C) HyperCreeck 2020
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/
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
#include "scanf.h"
#include "cbasic.h"
#include "interrupt.h"

// Create variables
char line[1024];
const char *cargv[100];
int cargc;
int scargv;

// Our main function!
int cbasic()
{
    // Let's print the name and some Commodore 64 BASIC related stuff!
    // This must be before the loop!
    printf("     **** CADEX CBASIC V1 ****    \n\n");
    printf("64K RAM SYSTEM  38911 BASIC BYTES FREE\n");
    // The loop starts!
    while (1)
    {
        // Print "Ready.""
        printf("\nREADY.\n");
        // Take input from user
        scanf(line, sizeof(line));
        // Number of arguments
        cargc = 0;
        // LEXER!!!
        // This is similar to cargv.split(" ") in JavaScript
        cargv[cargc] = strtok(line, " ");
        // Note that C does not have a string type. So, we have to look every character and remove the whitespace.
        while (cargv[cargc])
        {
            cargc++;
            cargv[cargc] = strtok(0, " ");
        }
        // If we don't check the length of input, the OS will crash. Because this is on the core part of the OS, we cannot let the OS crash due to this.
        if (cargc > 0)
        {
            // PARSER!!!
            if (!strcmp(cargv[0], "print") || !strcmp(cargv[0], "PRINT"))
            {
                scargv = cargc;
                for (size_t i = 1; i < scargv; i++)
                {
                    printf("%s ", cargv[i]);
                }
                printf("\n");
            }
            else if (!strcmp(cargv[0], "exit") || !strcmp(cargv[0], "EXIT"))
            {
                break;
            }
            else if (!strcmp(cargv[0], "poke") || !strcmp(cargv[0], "POKE"))
            {
                outb(str2int(cargv[1], sizeof(cargv[1])), str2int(cargv[2], sizeof(cargv[2])));
                printf("\n");
            }
            else if (!strcmp(cargv[0], "emoji") || !strcmp(cargv[0], "EMOJI"))
            {
                int pchar;
                int uchar;
                str2int(cargv[1], pchar);
                if (strncmp(cargv[1], "", sizeof(cargv[1])))
                {
                    printf(pchar);
                }
                else
                {
                    printf("?SYNTAX  ERROR");
                }
            }
            else if (!strcmp(cargv[0], "peek") || !strcmp(cargv[0], "PEEK"))
            {
                printf(20182183737);
            }
            else
            {
                printf("?SYNTAX  ERROR\n");
            }
            // Because this is a simple interpreter and this CBasic does not have line numbers or other things, we only have a lexer and a parser
        }
    }
}