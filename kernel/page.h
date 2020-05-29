/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef PAGE_H
#define PAGE_H

#include "kernel/types.h"

void  page_init();
void *page_alloc(bool zeroit);
void  page_free(void *addr);
void  page_stats( uint32_t *nfree, uint32_t *ntotal );

#endif
