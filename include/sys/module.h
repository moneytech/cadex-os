/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#pragma once

#include <types.h>

#include <library/hashmap.h>

typedef struct {
    char * name;
    int (* initialize)(void);
    int (* finalize)(void);
} module_defs;

typedef struct {
    module_defs * mod_info;
    void * bin_data;
    hashmap_t * symbols;
    uintptr_t end;
    size_t deps_length;
    char * deps;
    uintptr_t text_addr;
} module_data_t;

void (* symbol_find(const char * name))(void);

extern int module_quickcheck(void * blob);
extern void * module_load_direct(void * blob, size_t size);
extern void * module_load(char * filename);
extern void module_unload(char * name);
extern void modules_install(void);

#define MODULE_DEF(n,init,fini) \
        module_defs module_info_ ## n = { \
            .name       = #n, \
            .initialize = &init, \
            .finalize   = &fini \
        }

extern hashmap_t * modules_get_list(void);
extern hashmap_t * modules_get_symbols(void);

#define MODULE_DEPENDS(n) \
    static char _mod_dependency_ ## n [] __attribute__((section("moddeps"), used)) = #n
