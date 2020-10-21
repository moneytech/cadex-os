#include <kernel/gfxstream.h>
#include <kernel/types.h>
#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/string.h>
#include <library/stdbool.h>
#include <library/math.h>
#include <library/assert.h>
#include "stdarg.h"

#define BUFF_SIZE 1024
void wio(uint32_t timer_count);
void wait(uint32_t timer_count);
