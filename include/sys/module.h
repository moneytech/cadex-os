/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Stub files for dynamic libraries
 */

#pragma once

#include <library/hashmap.h>
#include <types.h>

typedef struct {
    int size;
    char *filename;
    uint8_t entry_point;
} dlib_t;

int dlopen(const char *path, dlib_t *dlib);
void dlclose(dlib_t dlib);
int dlfindsymbol(dlib_t dlib);
