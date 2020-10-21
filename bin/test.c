#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	/* 1. Signed integer overflow */
    printf("Test 1: Signed integer overflow\n");
    int error = 2147483633;
    char stop = -1;
    while (stop == -1) {
        render_window(WN_STDWINDOW);
        printf("\r%d", error);
        sleepThread(1);
        read_object_nonblock(STDIN, &stop, 1);
        error++;
    }
    printf("\n");
    /* 2. Accessing freed pointers */
    printf("Test 2: Accessing freed pointers\n");
    int a = malloc(sizeof(int));
    a = 1;
    free(a);
    printf("%d", a);
}