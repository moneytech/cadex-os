#include <stdio.h>
#include <truegl/truegl.h>
#include <library/printf.h>

char *test;

int main(int argc, char *argv[]) {
    // sprintf(test, "This is a %s which has %d letters", "test", 4);
    printf("%s", test);
    return 0;
}
 