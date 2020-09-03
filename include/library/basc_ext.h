/**
 * BasicC - A BASIC Language  extension to the C Language
*/


#ifndef BASICC_BASICC_H
#define BASICC_BASICC_H
#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>
#include <library/string.h>
#include <library/scanf.h>
#include <library/malloc.h>
#include <library/stddef.h>
#include <library/types.h>
#define out(a, ...) printf(a, __VA_ARGS__);

// keywords
#define do {
#define end }
#define then )
#define Sub void
#define else \
    }        \
    else
#define if if(

// logic operators
#define or ||
#define and &&
#define leq <=
#define greq =>
#define is ==
#define not !

// Some useful Assembly-like instructions
#define jge
#define jle
#define jnle
#define jnge
#define jne

#define Var
#define As
#define Integer int

#define exit return 0;

#define lengthof(a) strlen(a)
#endif // !BASICC_BASICC_H