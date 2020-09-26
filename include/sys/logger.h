#ifndef A647000C_7AE1_48FA_B3A9_9B6063D808D4
#define A647000C_7AE1_48FA_B3A9_9B6063D808D4

#include <stdio.h>
#include <library/color.h>

#define LOG(pchar, ...) printf(pchar, __VA_ARGS__);
#define ELOG(pchar, ...)            \
    {                               \
        setTextColor(CLEAR_RED, 0); \
        printf(pchar, __VA_ARGS__); \
        resetColor();               \
    }

#endif /* A647000C_7AE1_48FA_B3A9_9B6063D808D4 */
