/**
 * 
 * Cadex IfBasic Ver 0.1.2
 * ========================
 * Copyright © HyperCreeck 2020 
 * Licensed under CC BY SA 2.0
 * 
 */
#include "ifbasic.h"
#include "includeall.h"
#include "interrupt.h"

static int ifbasic(int iargc, const char **iargv){
    const char *srccode = iargv[0];
    const int pokeone = iargv[1];
    const int poketwo = iargv[2];
    if (!strcmp(srccode, "print"))
    {
        printf(srccode);
    }
    else if (!strcmp(srccode, "poke"))
    {
        if(pokeone > 0 && poketwo > 0){
            outb(pokeone, poketwo);
        } else
        {
            printf("Error: expression expected");
        }
        
    }
    else if (!strcmp(srccode, "peek"))
    {
        /* code */
    }
    else if (!strcmp(srccode, "pen"))
    {
        printf("!!!!PEN!!!!");
    }
    else
    {
        return 1;
    }
}