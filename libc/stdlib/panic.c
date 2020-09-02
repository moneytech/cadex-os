#include <stdio.h>

void PANIC(char *sender, char *str){
    printf("[PANIC] %s: %s", sender, str);
}