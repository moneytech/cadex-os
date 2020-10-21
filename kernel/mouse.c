/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#include "mouse.h"
#include "console.h"
#include "interrupt.h"
#include "ioports.h"
#include "kernel/ascii.h"
#include "kernelcore.h"
#include "process.h"

/**
 * The PS2 interface uses a data port and a command port.
 * Reading the command port yields a status uint8_t,
 * while writing to the command port executes commands.
 */

#define PS2_DATA_PORT    0x60
#define PS2_COMMAND_PORT 0x64

/* Some commands that may be sent to the command port. */

#define PS2_COMMAND_READ_CONFIG      0x20
#define PS2_COMMAND_WRITE_CONFIG     0x60
#define PS2_COMMAND_DISABLE_MOUSE    0xA7
#define PS2_COMMAND_ENABLE_MOUSE     0xA8
#define PS2_COMMAND_DISABLE_KEYBOARD 0xAD
#define PS2_COMMAND_ENABLE_KEYBOARD  0xAE
#define PS2_COMMAND_MOUSE_PREFIX     0xD4

/* The status uint8_t read from the command port has these fields. */

#define PS2_STATUS_OBF  0x01 // true: may not write to data port
#define PS2_STATUS_IBF  0x02 // true: may read from data port
#define PS2_STATUS_SYS  0x04 // true when port is initialized
#define PS2_STATUS_A2   0x08 // true if command port was last written to
#define PS2_STATUS_INH  0x10 // true if keyboard inhibited
#define PS2_STATUS_MOBF 0x20 // true if mouse output available
#define PS2_STATUS_TOUT 0x40 // true if timeout during I/O
#define PS2_STATUS_PERR 0x80 // true indicates parity error

/**
 * In addition, a configuration uint8_t may be read/written
 * via PS2_COMMAND_READ/WRITECONFIG.  The configuration uint8_t
 * has these bitfields.
 */

#define PS2_CONFIG_PORTA_IRQ       0x01
#define PS2_CONFIG_PORTB_IRQ       0x02
#define PS2_CONFIG_SYSTEM          0x04
#define PS2_CONFIG_RESERVED1       0x08
#define PS2_CONFIG_PORTA_CLOCK     0x10
#define PS2_CONFIG_PORTB_CLOCK     0x20
#define PS2_CONFIG_PORTA_TRANSLATE 0x40
#define PS2_CONFIG_RESERVED2       0x80

/**
 * The mouse has several specialized commands that may
 * be sent by first sending PS2_COMMAND_MOUSE_PREFIX,
 * then one of the following:
 */

#define PS2_MOUSE_COMMAND_ENABLE_STREAMING 0xea
#define PS2_MOUSE_COMMAND_ENABLE_DEVICE    0xf4
#define PS2_MOUSE_COMMAND_RESET            0xff

// Mouse.inc by SANiK
// License: Use as you wish, except to cause damage
uint8_t mouse_cycle = 0;        // unsigned char
unsigned char mouse_uint8_t[3]; // signed char
unsigned char mouse_x = 0;      // signed char
unsigned char mouse_y = 0;      // signed char
unsigned char mouse_button = 0;

uint8_t buffer[3];
uint8_t offset;
uint8_t buttons;

uint8_t mouse_read();

char *mouse_bitmap = "   *       ."
                     "   **      ."
                     "   ***     ."
                     "   ****    ."
                     "   *****   ."
                     "   ******  ."
                     "   ******  ."
                     "   *****   ."
                     "   ****    .";

void DrawBitmap(char *bitmap, int x, int y) {
    int ux = x;
    int uy = y;
    while (*bitmap) {
        if (*bitmap == '*') {
            graphics_rect(&graphics_root, ux, uy, 5, 5);
            ux++;
        } else if (*bitmap == '.') {
            ux = x;
            uy++;
        } else if (*bitmap == ' ') {
            ux++;
        }
        *bitmap++;
    }
}
// Mouse functions
static void
mouse_handler(int i, int code) // struct regs *a_r (not used but just there)
{
    uint8_t status = inb(0x64);
    if (!(status & 0x20))
        return;
    // buffer[offset] = inb(0x60);

    // offset = (offset + 1) % 3;

    // if (offset == 0) {
    //     if (buffer[1] != 0 || buffer[2] != 0) {
    //         // DrawBitmap(mouse_bitmap, (int8_t)buffer[1],
    //         -((int8_t)buffer[2]));
    //     }

    //     for (uint8_t i = 0; i < 3; i++) {
    //         if ((buffer[0] & (0x1 << i)) != (buttons & (0x1 << i))) {
    // if (buttons & (0x1 << i))
    //     kprintf("OnMouseUp\n");
    // else
    //     kprintf("OnMouseDown\n");
    //         }
    //     }
    //     buttons = buffer[0];
    // }
    switch (mouse_cycle) {
        case 0:
            mouse_uint8_t[0] = inb(0x60);
            mouse_cycle++;
            break;
        case 1:
            mouse_uint8_t[1] = inb(0x60);
            mouse_cycle++;
            break;
        case 2:
            mouse_uint8_t[2] = inb(0x60);
            mouse_x = mouse_x + (mouse_uint8_t[1]);
            mouse_y = mouse_y - (mouse_uint8_t[2]);
            mouse_button = mouse_uint8_t[0];
            mouse_cycle = 0;
            if (mouse_x < 0)
                mouse_x = 0;
            if (mouse_y < 0)
                mouse_y = 0;
            if (mouse_x > video_xres)
                mouse_x = video_xres - 1;
            if (mouse_y > video_yres)
                mouse_y = video_yres - 1;
            if (mouse_uint8_t[1] != 0 && mouse_uint8_t[2] != 0) {
                graphics_clear(&graphics_root, 0, 0, video_xres, video_yres);
                // clock_wait(1);
                DrawBitmap(mouse_bitmap, mouse_x, mouse_y);
            }
            for (uint8_t i = 0; i < 3; i++)
                if ((mouse_uint8_t[0] & (0x1 << i)) !=
                    (mouse_uint8_t[0] & (0x1 << i)))
                    if (mouse_uint8_t[0] & (0x1 << i))
                        kprintf("OnMouseUp\n");
                    else
                        DrawBitmap(mouse_bitmap, mouse_x, mouse_y);
            break;
    }
    // kprintf("X=%u,Y=%u,B=%u\n", mouse_x, mouse_y, mouse_button);
}

static inline void mouse_wait(uint8_t a_type) // unsigned char
{
    uint32_t _time_out = 100000; // unsigned int
    if (a_type == 0) {
        while (_time_out--) // Data
        {
            if ((inb(0x64) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (_time_out--) // Signal
        {
            if ((inb(0x64) & 2) == 0) {
                return;
            }
        }
        return;
    }
}

static inline void mouse_write(uint8_t a_write) // unsigned char
{
    // Wait to be able to send a command
    mouse_wait(1);
    // Tell the mouse we are sending a command
    outb(0xD4, 0x64);
    // Wait for the final part
    mouse_wait(1);
    // Finally write
    outb(a_write, 0x60);
}

uint8_t mouse_read() {
    // Get's response from mouse
    mouse_wait(0);
    return inb(0x60);
}

void mouse_init() {
    uint8_t _status; // unsigned char

    // Enable the auxiliary mouse device
    mouse_wait(1);
    outb(0xA8, 0x64);

    // Enable the interrupts
    mouse_wait(1);
    outb(0x20, 0x64);
    mouse_wait(0);
    _status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x60, 0x64);
    mouse_wait(1);
    outb(_status, 0x60);

    // Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read(); // Acknowledge

    // Enable the mouse
    mouse_write(0xF4);
    mouse_read(); // Acknowledge

    // Setup the mouse handler
    interrupt_register(44, mouse_handler);
    interrupt_enable(44);
}
