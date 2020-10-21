#include <stdlib.h>
#include <stdio.h>

/**
 * Delete function for C++
*/
void delete(void *a){
    free(&a);
}