/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Yamaha YM3812 (OPL2) sound card driver
 */

#include "adlib.h"
#include "kernel/types.h"

uint16_t Adlib_BaseAddress = 0x388;
uint16_t Adlib_DataPort = 0x389;

uint8_t Adlib_IRQ = 8;
int Adlib_Present = 0;

int adlib_init(void) {
    // Try to find an Adlib card
    kprintf("[adlib] searching for an Adlib compatible device...\n");

    // Reset both timers
    Adlib_Write(
        REG_TIMER_CONTROL,
        TIMER_CTRL_TIMER1_MASK |
            TIMER_CTRL_TIMER2_MASK); // Not sure why this first step is needed
    Adlib_Write(REG_TIMER_CONTROL, TIMER_CTRL_IRQ_RESET);

    uint8_t status = Adlib_Read(REG_STATUS);

    // Write 0xff to timer 1 register
    Adlib_Write(REG_TIMER1_VALUE, 0xFF);

    // Start Timer 1
    Adlib_Write(REG_TIMER_CONTROL,
                TIMER_CTRL_TIMER2_MASK | TIMER_CTRL_TIMER1_GO);

    // Delay for at least 80 microseconds (already done in Adlib_Write)
    wait_for_io(1);

    // Read the status register again
    uint8_t status2 = Adlib_Read(REG_STATUS);

    // Reset both timers and interrupts (not sure why but the instructions say
    // to do this)
    Adlib_Write(REG_TIMER_CONTROL,
                TIMER_CTRL_TIMER1_MASK |
                    TIMER_CTRL_TIMER2_MASK); // Still not sure why this is
                                             // needed, if indeed it is
    Adlib_Write(REG_TIMER_CONTROL, TIMER_CTRL_IRQ_RESET);

    // Test the stored status
    if ((status & 0xE0) == 0) {
        // test the second stored status
        if ((status2 & 0xE0) == 0xC0) {
            kprintf("[adlib] found an Adlib compatible device at 0x%x\n",
                    Adlib_BaseAddress);
            Adlib_Present = 1;
        }
    }

    if (!Adlib_Present)
        kprintf("[adlib] no Adlib compatible device found\n");

    return Adlib_Present;
}

uint8_t Adlib_Read(uint8_t reg) { return inb(Adlib_BaseAddress + reg); }

void Adlib_Reset(void) {
    dbg_printf("[adlib] resetting Adlib... ");

    // Quick-and-dirty reset: write 0's to all 245 registers
    for (uint8_t reg = 1; reg < 0xF5; ++reg) {
        Adlib_Write(reg, 0);
    }

    dbg_printf("done\n");
}

void Adlib_Sound_Off() { Adlib_Write(0xB0, 0x11); }

void Adlib_Test(void) {
    Adlib_Reset();

    // make some goddamned sound!
    Adlib_Write(0x20, 0x01);
    Adlib_Write(0x40, 0x10);
    Adlib_Write(0x60, 0xF0);
    Adlib_Write(0x80, 0x77);
    Adlib_Write(0xA0, 0x98);
    Adlib_Write(0x23, 0x01);
    Adlib_Write(0x43, 0x00);
    Adlib_Write(0x63, 0xF0);
    Adlib_Write(0x83, 0x77);
    Adlib_Write(0xB0, 0x31);

    wait_for_io(10000000000);

    // turn the voice off
    Adlib_Sound_Off();
}

void Adlib_Write(uint8_t reg, uint8_t value) {
    // select the register
    outb(reg, Adlib_BaseAddress);

    // wait 3.3 microseconds
    wait_for_io(1);

    // Write to the register
    outb(value, Adlib_DataPort);

    // We're supposed to wait 23 microseconds before any other sound card
    // operation can be performed (Realistically, waiting doesn't matter because
    // the hardware is probably emulated)
    wait_for_io(1);
}
