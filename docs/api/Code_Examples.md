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

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
    syscall_chdir("/");

    int dir_fd = syscall_open_file("/", 0, 0);
    syscall_object_set_tag(dir_fd, "ROOT");

    int fd = syscall_open_file("ROOT:/data/words", 0, 0);
    char buffer[1000];
    int n;

    while ((n = read_object(fd, buffer, 100)) > 0) {
        buffer[n] = 0;
        printf("%s", buffer);
    }

    syscall_object_close(fd);
    return 0;
}

```

##
