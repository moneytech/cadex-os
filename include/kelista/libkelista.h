#ifndef LIBKELISTA_H
#define LIBKELISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <library/types.h>

typedef int ke_obj_int;
typedef char* ke_obj_char;
typedef struct ke_obj_struct
{
    int charname;
};
#define KELISTA_VER "0.1.1"
#define SUPPORT_KELISTA false
#define def void
#define public
#define private public
#define protected private 
#define internal protected
#define virtual internal
#define override virtual
#define class struct 
#endif // LIBKELISTA_H