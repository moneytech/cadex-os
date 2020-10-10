/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef INTERRUPT_H
#define INTERRUPT_H

typedef void (*interrupt_handler_t)(int intr, int code);

extern unsigned int __irq_sem;

#define IRQ_OFF              \
    {                        \
        asm volatile("cli"); \
        __irq_sem++;         \
    }
#define IRQ_ON                   \
    {                            \
        if (__irq_sem > 0)       \
            __irq_sem--;         \
        if (!__irq_sem)          \
            asm volatile("sti"); \
    }
#define IRQ_RES              \
    {                        \
        __irq_sem = 0;       \
        asm volatile("sti"); \
    }

void interrupt_init();
void interrupt_register(int i, interrupt_handler_t handler);
void interrupt_enable(int i);
void interrupt_disable(int i);
void interrupt_block();
void interrupt_unblock();
void interrupt_wait();

void beep();
/*
PC Interrupts:
IRQ	Interrupt
0	32	System Timer
1	33	Keyboard
2	34	Cascade
3	35	Serial Port 2
4	36	Serial Port 1
5	37	Parallel Port 2 or Sound Card
6	38	Floppy
7	39	Parallel Port 1
8	40	Real Time Clock
9	41	Network (or ATA 3)
10	42	Network/Sound/SCSI
11	43	SCSI Other (or ATA 2)
12	44	PS/2 Mouse
13	45	FPU
14	46	ATA 0
15	47	ATA 1
*/

#endif
