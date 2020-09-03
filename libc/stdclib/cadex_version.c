/**
 * cadex_version.c: Contains versioning info and functions returning version info about Cadex OS
 * 
 * This file is a part of the Standard Cadex Library
*/

#include <stdclib.h>

// Return UTS_RELEASE constant defined in 'library/version.h'
char *get_system_version(){
    // Return UTS_RELEASE
    return UTS_RELEASE;
}