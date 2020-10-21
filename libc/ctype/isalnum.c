#include <ctype.h>

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

// weak_alias(__isalnum_l, isalnum_l);
