#ifndef STDCLIB_H
#define STDCLIB_H

#include <library/types.h>
#include <library/malloc.h>
#include <library/version.h>

// some cadex-specific attributes
#define __cdx_attrtib __INSERT_CDX_ATTRIBUTE()

// cadex_version.c
char *get_system_version();

// contty.c
int get_console_width(int window);
int get_console_height(int window);
#endif // !STDCLIB_H