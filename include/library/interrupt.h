#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <kernel/types.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
void wait_for_io(uint32_t timer_count);
void sleep(uint32_t timer_count);
static void play_sound(uint32_t nFrequence);
static void nosound();
void beep();
#endif