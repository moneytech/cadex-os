/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

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

/*
This is the C initialization point of the Cadex kernel.
By the time we reach this point, we are in protected mode,
with interrupts disabled, a valid C stack, but no malloc heap.
Now we initialize each subsystem in the proper order:
*/

int kernel_main()
{
	char a;
	struct graphics *g = graphics_create_root();

	console_init(g);
	console_addref(&console_root);

	printf("[SYS] video: %d x %d\n", video_xres, video_yres, video_xbytes);
	printf("[SYS] kernel: %d bytes\n", kernel_size);

	page_init();
	kmalloc_init((char *) KMALLOC_START, KMALLOC_LENGTH);
	interrupt_init();
	rtc_init();
	clock_init();
	mouse_init();
	keyboard_init();
	process_init();
	ata_init();
	cdrom_init();
	diskfs_init();
	kshell_mount("atapi", 2, "cdromfs");
	printf("\n>>>>>> Cadex OS Version 0.1.3 | beta-4.1 <<<<<<\n");
	kshell_launch();

	while(1) {
		console_putchar(&console_root,keyboard_read(a));
	}

	return 0;
}
