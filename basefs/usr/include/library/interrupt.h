/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <kernel/types.h>
#include <stdio.h>
#define COS_SOURCE // Define that this is Cadex-OS source

void interrupt_disable(int i);
void interrupt_enable(int i);

#endif
