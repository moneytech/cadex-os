/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef MOUSE_H
#define MOUSE_H

#include "ata.h"
#include "cdromfs.h"
#include "clock.h"
#include "console.h"
#include "device.h"
#include "diskfs.h"
#include "graphics.h"
#include "interrupt.h"
#include "kernel/ascii.h"
#include "kernel/syscall.h"
#include "kernelcore.h"
#include "keyboard.h"
#include "kmalloc.h"
#include "kprintf.h"
#include "kshell.h"
#include "memorylayout.h"
#include "mouse.h"
#include "page.h"
#include "process.h"
#include "rtc.h"
#include "serial.h"
#include "service.h"
#include "string.h"
#include <sysinfo.h>

struct mouse_event {
    int32_t x;
    int32_t y;
    uint8_t buttons;
};

void mouse_init();
float posx, posy;
float xscale, yscale;
#endif
