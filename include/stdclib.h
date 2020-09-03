#ifndef STDCLIB_H
#define STDCLIB_H

#include <library/types.h>
#include <library/malloc.h>
#include <library/version.h>

// some cadex-specific attributes
#define __cdx_attrtib __INSERT_CDX_ATTRIBUTE()

//! cadex_version.c
/**
 * Get the system version
 * @return char
*/
char *get_system_version();

//! contty.c
/**
 * Get the console width
 * @return int
*/
int get_console_width();
/**
 * Get the console height
 * @return int
*/
int get_console_height();
#endif // !STDCLIB_H