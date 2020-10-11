# Useful code snippets

Useful code snippets to use in CadexOS apps.

## Fork test

An example code for process forking

```c
#include <stdio.h>

int main(int argc, const char* argv[])
{
    printf("Hello World, I am %d.\n", syscall_process_self());
    int x = fork();
    printf("My fork returned %d\n", x);

    printf("Some numbers:\n");

    int i;
    for (i = 0; i < 5; ++i) {
        printf("%d\n", i);
    }
    return 0;
}
```

## Reading files

An example code for opening and reading files

