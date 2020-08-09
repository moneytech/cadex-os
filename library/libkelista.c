#include <stdio.h>
#include <stdlib.h>
#include <library/list_t.h>
#include <library/types.h>
#include <library/keyevents.h>
#include <kelista/libkelista.h>

bool isKelistaSupported(){
    if(SUPPORT_KELISTA){ 
        return true;
    }
}