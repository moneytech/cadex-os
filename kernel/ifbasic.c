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

static int ifbasic(int iargc, const char **iargv){
    const char *srccode = iargv[0];
    const int *pokeone = iargv[1];
    const int *poketwo = iargv[2];
    if (!strcmp(srccode, "print"))
    {
        printf("");
    }
    else if (!strcmp(srccode, "poke"))
    {
        
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