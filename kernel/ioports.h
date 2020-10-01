/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef IOPORTS_H
#define IOPORTS_H

#include "kernel/types.h"


/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64

/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */

#define KBRD_IO 0x60	/* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */

#define bit(n) (1 << (n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags)&bit(n))

/*
These are C wrappers around the assembly instruction IN and OUT
to move data to and from I/O ports.  These variants are historically
called inb/inw/inl outb/outw/outl for in/out of byte (8 bits),
word (16 bits), and long (32 bits) respectively.
Note that some devices requires the "slow" variants that do an
extra dummy I/O in order to give the device more time to respond.
*/

static inline uint8_t inb(int port)
{
	uint8_t result;
	asm("inb %w1, %b0"
		: "=a"(result)
		: "Nd"(port));
	return result;
}

static inline uint16_t inw(int port)
{
	uint16_t result;
	asm("inw %w1, %w0"
		: "=a"(result)
		: "Nd"(port));
	return result;
}

static inline uint16_t inl(int port)
{
	uint32_t result;
	asm("inl %w1, %0"
		: "=a"(result)
		: "Nd"(port));
	return result;
}

static inline void outb(uint8_t value, int port)
{
	asm("outb %b0, %w1"
		:
		: "a"(value), "Nd"(port));
}

static inline void outw(uint16_t value, int port)
{
	asm("outw %w0, %w1"
		:
		: "a"(value), "Nd"(port));
}

static inline void outl(uint32_t value, int port)
{
	asm("outl %0, %w1"
		:
		: "a"(value), "Nd"(port));
}

static inline void iowait()
{
	outb(0, 0x80);
}

static inline uint8_t inb_slow(int port)
{
	uint8_t result = inb(port);
	iowait();
	return result;
}

static inline uint16_t inw_slow(int port)
{
	uint16_t result = inw(port);
	iowait();
	return result;
}

static inline uint32_t inl_slow(int port)
{
	uint32_t result = inl(port);
	iowait();
	return result;
}

static inline void outb_slow(uint8_t value, int port)
{
	outb(value, port);
	iowait();
}

static inline void outw_slow(uint16_t value, int port)
{
	outw(value, port);
	iowait();
}

static inline void outl_slow(uint32_t value, int port)
{
	outl(value, port);
	iowait();
}

/* This functions tries to shutdown the virtual machine (if possible) */
static inline void shutdown_vm(){
	outw(0xB004, 0x0 | 0x2000);
	outw(0xB004, 0x2000);
	outw(0x4004, 0x3400);
	outw(0x604, 0x2000);
}

#endif
