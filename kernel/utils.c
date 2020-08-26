/**
 * Cadex Utility Library
 * (C) HyperCreeck 2020
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/
#include "utils.h"

int decToHex() {
    long decimalnum, quotient, remainder;
    int i, j = 0;
    char hexadecimalnum[100];

    printf("Enter decimal number: ");
    scanf("%ld", &decimalnum);

    quotient = decimalnum;

    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        quotient = quotient / 16;
    }

    // display integer into character
    for (i = j; i >= 0; i--)
        printf("%c", hexadecimalnum[i]);
    printf("\n");
    return 0;
}
extern void printTriangle(int rows_s) {
    int i, j, k, rows, count, temp=1;
    rows = rows_s;
    count=rows-1;
    for (i= 1; i <= rows; i++)
    {
        for (j=1;j<=count;j++) {
            printf(" ");
        }
        for (k=1;k<=temp;k++) {
            printf("*");
        }
        count--;
        temp+=2;
        printf("\n");
    }
}
extern void hardMath(int number1, int number2) {
    float j, k, l, m, n, i;
    i=number1 * number2 + number1 - number2 * number1 % number2 * number1 + number2 / 100 * 500030 * number2 / number2;
    k = i * number1;
    l = i * k + number1 * number2;
    printf("%d", l);
}