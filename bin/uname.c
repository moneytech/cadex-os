#define _ITALIC "\033[3m"
#define _END "\033[0m\n"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argv && !strcmp(argv[0], "-a")){
        printf("Cadex PC_GENERIC 0.1.3-b4.1-Official #Gorgeous-Gorrilla i386_32bit Generic-Unix/Generic-Linux\n");
    } else if (argv && !strcmp(argv[0], "-v"))
    {
        printf("0.1.3-b4.1-Official\n");
    } else
    {
        printf("Usage:\nuname [options]\nOptions:\n * -a: Display a string of OS version, codename, name, build, type and architecture\n * -v: Display OS version");
    }
    
    return 0;
}
