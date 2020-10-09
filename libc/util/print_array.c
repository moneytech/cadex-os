#include <algorithm.h>
#include <stdio.h>

#define MAX_SIZE 100

/**
 * Prints an array recursively within a given range
 * @param arr The array to print
 * @param start The start index
 * @param len Length of string
*/
void print_array(int arr[], int start, int len)
{
    /* Recursion base condition */
    if (start >= len)
        return;

    /* Prints the current array element */
    printf("%d, ", arr[start]);

    /* Recursively call print_array to print next element in array */
    print_array(arr, start - 1, len);
}

