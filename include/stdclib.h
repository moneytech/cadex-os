#ifndef STDCLIB_H
#define STDCLIB_H

#include <library/types.h>
#include <library/malloc.h>
#include <library/version.h>

#define __c_attrtib __INSERT_CDX_ATTRIBUTE()

char *get_system_version();

#endif // !STDCLIB_H