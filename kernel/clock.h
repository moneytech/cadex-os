/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef CLOCK_H
#define CLOCK_H

#include "kernel/types.h"

typedef struct clock_t {
    uint32_t seconds;
    uint32_t millis;
} clock_t;

void clock_init();
clock_t clock_read();
clock_t clock_diff(clock_t start, clock_t stop);
void clock_wait(uint32_t millis);

#endif
