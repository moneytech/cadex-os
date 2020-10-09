#include "library/string.h"
#include "library/syscalls.h"

int main(int argc, char* argv[])
{
    printf("hello world, I am %d.\n", syscall_process_self());
    int x = fork();
    printf("My fork returned %d\n", x);

    printf("Some numbers:\n");

    int i;
    for (i = 0; i < 5; ++i) {
        printf("%d\n", i);
    }
    return 0;
}
