#define _ITALIC "\033[3m"
#define _END "\033[0m\n"

#include <library/stdio.h>

int main(int argc, char const *argv[])
{
    if (argv[1] == "-a")
    {
        printf("Cadex PC_GENERIC 0.1.3-b4.1-Official #Gorgeous-Gorrilla i386_32bit Generic-Unix/Generic-Linux");
    }
    else
    {
        printf("Cadex");
    }
    return 0;
}
