/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

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
#include "pci.h"
#include "process.h"
#include "rtc.h"
#include "serial.h"
#include "service.h"
#include "string.h"
#include "adlib.h"
#include <sysinfo.h>

/*
This is the C initialization point of the Cadex OS.
By the time we reach this point, we are in protected mode,
with interrupts disabled, a valid C stack, but no malloc heap.
Now we initialize each subsystem in the proper order:
*/

int kernel_main()
{
    char a;
    struct graphics* g = graphics_create_root();

    // init the console
    console_init(g);
    // add reference to console_root
    console_addref(&console_root);

    // print the screen resolution
    kprintf("[SYS] video: %d x %d\n", video_xres, video_yres, video_xbytes);
    // print the kernel size
    kprintf("[SYS] kernel size: %d KB\n", kernel_size / 1000);

    // init serialports
    serial_init();
    // init paging
    page_init();
    // init kernel memory allocator
    kmalloc_init((char*)KMALLOC_START, KMALLOC_LENGTH);
    // init interrupt manager
    interrupt_init();
    // init realtime clock
    rtc_init();
    // init system clock
    clock_init();
    // init mouse
    mouse_init();
    // init keyboard
    keyboard_init();
    // init process manager
    process_init();
    // init ata driver
    ata_init();
    // init atapi(cdrom) driver
    cdrom_init();
    // init filesystem driver
    diskfs_init();
	// init adlib driver
    adlib_init();
	// init ACPI driver
    acpi_init();
    // mount atapi device with unit 2
    kshell_mount("atapi", 2, "cdfs");
#ifdef DEBUG
    kprintf("\nCadex OS %sb-%s <<<<<<\n", SYS_VER, SYS_BUILD); // #define debug to enable version info
#endif
    kprintf("\n");
    // start the necessary services
    service_start("/bin/dbusctl.exe", 0, 0, "DBus Controller");
    service_start("/bin/klog.exe", 0, 0, "Kernel logging helper");
	// show login prompt
    kshell_show_login_prompt();
    // launch shell
    kshell_launch();
    dbg_printf("[kmain] Launched kshell\n");
    while (1) {
        // we need this for the kshell or it will just show text and we can't type anything into it
        console_putchar(&console_root, keyboard_read(a));
    }

    return 0;
}
