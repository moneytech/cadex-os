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

void ifbasexec(char *srccode){
    if (!strcmp(srccode, "print"))
    {
        printf("");
    }
    else if (!strcmp(srccode, "poke"))
    {
        /* code */
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
        /* code */
    }
    
}