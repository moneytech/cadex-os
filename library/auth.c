#include "auth.h"

extern int getAuth()
{
    char *passwd[1024];
password:
    printf("sudo: password for root: ");
    scanf(passwd, sizeof(passwd));
    if (!strcmp(passwd, "root"))
    {
        _process_exit(0);
        return 0;
    }
    else
    {
        printf("sudo: Wrong password\n");
        goto password;
    }
}