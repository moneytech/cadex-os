#include <stdio.h>
#include <library/scanf.h>
#include <passwd.h>

int tmp1;

extern int getAuth()
{
    char *passwd[1024];

password:
    printf("sudo: password for root: ");
    passwd_scanf(passwd, sizeof(passwd));
    if (!strcmp(passwd, "root"))
    {
        return 0;
    }
    else
    {
        printf("\nsudo: wrong password\n");
        if (tmp1 > 1)
        {
            printf("sudo: %d incorrect login attempts\n", tmp1 + 1);
            return 1;
        }
        tmp1 += 1;
        goto password;
    }
}

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        if (!strcmp(argv[0], "-i"))
        {
            getAuth();
            printf("\n");
        }
        else
        {
            printf("sudo: invalid option: %s", argv[0]);
        }
    }
    else
    {
        printf("usage: sudo -i\n");
    }
    return 0;
}