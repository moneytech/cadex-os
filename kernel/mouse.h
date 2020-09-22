/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef MOUSE_H
#define MOUSE_H

#include "console.h"
#include "page.h"
#include "process.h"
#include "interrupt.h"
#include "keyboard.h"
#include "mouse.h"
#include "clock.h"
#include "ata.h"
#include "device.h"
#include "cdromfs.h"
#include "string.h"
#include "graphics.h"
#include "kernel/ascii.h"
#include "kernel/syscall.h"
#include "rtc.h"
#include "kernelcore.h"
#include "kmalloc.h"
#include "memorylayout.h"
#include "kshell.h"
#include "cdromfs.h"
#include "diskfs.h"
#include "serial.h"
#include <sysinfo.h>
#include "printf.h"
#include "service.h"

struct mouse_event {
	uint8_t buttons;
	int32_t x;
	int32_t y;
};

void mouse_read(struct mouse_event *e);
void mouse_init();

#endif
