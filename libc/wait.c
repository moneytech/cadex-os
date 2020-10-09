/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/* I/O wait functions */
#include <wait.h>

static char stdio_buffer[PAGE_SIZE] = {0};

static uint32_t stdio_buffer_index = 0;

void wio(uint32_t timer_count)
{
    while (1)
    {
        asm volatile("nop");
        timer_count--;
        if (timer_count <= 0)
            break;
    }
}
// Sets the CPU to noop mode for specified milliseconds
void wait(uint32_t timer_count)
{
    wio(timer_count * 0x02FFFFFF);
}