/**
 * Cadex CBasic
 * (C) HyperCreeck 2020
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/
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
#include "scanf.h"
#include "cbasic.h"
#include "interrupt.h"

char line[1024];
const char *cargv[100];
int cargc;
int scargv;

int cbasic(){
    while(1){
        scanf(line, sizeof(line));
        cargc = 0;
        cargv[cargc] = strtok(line, " ");
        while (cargv[cargc])
        {
            cargc++;
            cargv[cargc] = strtok(0, " ");
        }
        if (cargc > 0)
        {
            if (!strcmp(cargv[0], "print"))
            {
                scargv = cargc;
                for (size_t i = 1; i < scargv; i++)
                {
                    printf("%s ", cargv[i]);
                }
                printf("\n");
            }
            else if (!strcmp(cargv[0], "exit"))
            {
                break;
            }
            else if (!strcmp(cargv[0], "poke"))
            {
                outb(str2int(cargv[1], sizeof(cargv[1])), str2int(cargv[2], sizeof(cargv[2])));
                printf("\n");
            }
            else if (!strcmp)
            {
                
            }
            else
            {
                printf("?Syntax error\n");
            }
        }
    }

}