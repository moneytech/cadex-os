#include "panic.h"

void PANIC(char *sender, char *str)
{
    kprintf("[PANIC] %s: %s", sender, str);
}