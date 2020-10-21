/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include <library/types.h>
#include <stdio.h>

char *ctime(const time_t *timep) { return syscall_system_time(timep); }

/* EOF */