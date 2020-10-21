/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * libbmf: BitMapFont reader
 * @author HyperCreeck
 */

#include <stdio.h>
#include <libbmp/bitmap.h>

typedef struct
{
    uint32_t size;
    char *font_type;
} bmf_font_t;
