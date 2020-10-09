#include "ata.h"
#include "bcache.h"
#include "bitmap.h"
#include "clock.h"
#include "console.h"
#include "fs.h"
#include "kernelcore.h"
#include "keyboard.h"
#include "kmalloc.h"
#include "kprintf.h"
#include "kshell.h"
#include "main.h"
#include "page.h"
#include "process.h"
#include "rtc.h"
#include "string.h"
#include "syscall_handler.h"
#include <kernel/ascii.h>
#include <kernel/error.h>
#include <kernel/syscall.h>
#include <kernel/types.h>

int service_start(char* path, int argc, char* argv[], char* s_name);

