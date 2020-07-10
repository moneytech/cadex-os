#include <library/ctype.h>
#include <library/const.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/stdio.h>
#include <library/syscalls.h>

extern void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));