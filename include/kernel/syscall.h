/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H

#include "kernel/error.h"
#include "kernel/types.h"

typedef enum {
    SYSCALL_DEBUG,
    SYSCALL_DEBUG_PUTC,
    SYSCALL_PROCESS_YIELD,
    SYSCALL_PROCESS_EXIT,
    SYSCALL_PROCESS_RUN,
    SYSCALL_PROCESS_WRUN,
    SYSCALL_PROCESS_FORK,
    SYSCALL_PROCESS_EXEC,
    SYSCALL_PROCESS_SELF,
    SYSCALL_PROCESS_PARENT,
    SYSCALL_PROCESS_KILL,
    SYSCALL_PROCESS_REAP,
    SYSCALL_PROCESS_WAIT,
    SYSCALL_PROCESS_SLEEP,
    SYSCALL_PROCESS_STATS,
    SYSCALL_PROCESS_HEAP,
    SYSCALL_OPEN_FILE,
    SYSCALL_OPEN_FILE_RELATIVE,
    SYSCALL_OPEN_DIR,
    SYSCALL_OPEN_WINDOW,
    SYSCALL_OPEN_CONSOLE,
    SYSCALL_OPEN_PIPE,
    SYSCALL_OBJECT_TYPE,
    SYSCALL_OBJECT_DUP,
    SYSCALL_OBJECT_READ,
    SYSCALL_OBJECT_READ_NONBLOCK,
    SYSCALL_OBJECT_LIST,
    SYSCALL_OBJECT_WRITE,
    SYSCALL_OBJECT_SEEK,
    SYSCALL_OBJECT_SIZE,
    SYSCALL_OBJECT_COPY,
    SYSCALL_OBJECT_REMOVE,
    SYSCALL_OBJECT_CLOSE,
    SYSCALL_OBJECT_STATS,
    SYSCALL_OBJECT_SET_TAG,
    SYSCALL_OBJECT_GET_TAG,
    SYSCALL_OBJECT_SET_BLOCKING,
    SYSCALL_OBJECT_MAX,
    SYSCALL_SYSTEM_STATS,
    SYSCALL_BCACHE_STATS,
    SYSCALL_BCACHE_FLUSH,
    SYSCALL_SYSTEM_TIME,
    SYSCALL_SYSTEM_RTC,
    SYSCALL_DEVICE_DRIVER_STATS,
    SYSCALL_CHDIR,
    SYSCALL_MOUSE_READ,
    SYSCALL_BGCOLOR,
    SYSCALL_KPANIC,
    SYSCALL_BEEP,
    MAX_SYSCALL // must be the last element in the enum
} syscall_t;

uint32_t syscall(syscall_t s, uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                 uint32_t e);

#endif
