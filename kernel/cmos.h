
#include <kernel/types.h>
#include <kernel/ascii.h>
#include <kernel/types.h>
#include <kernel/syscall.h>
#include <kernel/error.h>
#include <kernel/types.h>
#include "kshell.h"
#include "keyboard.h"
#include "console.h"
#include "string.h"
#include "rtc.h"
#include "kmalloc.h"
#include "page.h"
#include "process.h"
#include "main.h"
#include "fs.h"
#include "syscall_handler.h"
#include "clock.h"
#include "kernelcore.h"
#include "bcache.h"
#include "kprintf.h"
#include "ata.h"
#include "bitmap.h"

extern void get_time(uint16_t *hours, uint16_t *minutes, uint16_t *seconds);
extern void get_date(uint16_t *month, uint16_t *day);
extern uint32_t boot_time;
extern uint32_t read_cmos(void);
