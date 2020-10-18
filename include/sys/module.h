/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * Stub files for dynamic libraries
*/

#pragma once

#include <types.h>
#include <library/hashmap.h>

typedef struct
{
    int size;
    char *filename;
    uint8_t entry_point;
} dlib_t;

int dlopen(const char *path, dlib_t *dlib);
void dlclose(dlib_t dlib);
int dlfindsymbol(dlib_t dlib);
