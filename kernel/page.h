/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef PAGE_H
#define PAGE_H

#include "kernel/types.h"

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_RW      (1 << 1)
#define PAGE_FLAG_BITMAP_END \
    (0x5 << 9) // use the 3-bit unused in PageTable entry as flag
#define PAGE_FLAG_BITMAP_START (0x2 << 9)

void page_init();
void *page_alloc(bool zeroit);
void page_free(void *addr);
void page_stats(uint32_t *nfree, uint32_t *ntotal);
#endif
