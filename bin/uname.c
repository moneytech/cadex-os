#include <stdio.h>
#include <library/version.h>

int main(int argc, char const *argv[])
{
    if (argv && !strcmp(argv[0], "-a"))
    {
        printf("CadexOS version %s; Codename \"%s\" %s\n", _LTS_REL_, _K_CODENAME, _K_ARCH);
    }
    else if (argv && !strcmp(argv[0], "-v"))
    {
        printf("%s-%s\n", _LTS_REL_, __VER_SUFFIX);
    }
    else
    {
        printf("Usage:\nuname [options]\nOptions:\n * -a: Display a string of OS version, codename, name, build, type and architecture\n * -v: Display OS version");
    }

    return 0;
}
