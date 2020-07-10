#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/ascii.h>
#include <library/strtoui.h>
#include <library/string.h>
#include <library/float.h>
#include <library/qsort.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/rand.h>

void __assert_func(const char * file, int line, const char * func, const char * failedexpr) {
 printf("Assertion failed in %s:%d (%s): %s\n"/*, file, line, func, failedexpr*/);
 // void
}
