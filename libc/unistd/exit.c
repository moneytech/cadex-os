#include <stdlib.h>
#include <unistd.h>

void exit(int val)
{
    _handle_atexit();
    _exit(val);
}
