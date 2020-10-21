/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef _LOGGER_H
#define _LOGGER_H

#include <debug.h>
#include <library/color.h>
#include <stdio.h>

#define LOG(pchar, ...)  dbg_printf(pchar, __VA_ARGS__);
#define ELOG(pchar, ...) dbg_printf(pchar, __VA_ARGS__);

#endif /* A647000C_7AE1_48FA_B3A9_9B6063D808D4 */
