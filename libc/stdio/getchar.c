#include <stdio.h>

int getchar(void)
{
	int x;
	read_object(0, x, 1);
	return x;
}
