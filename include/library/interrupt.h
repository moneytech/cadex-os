#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <kernel/types.h>
#include <stdio.h>

void interrupt_disable(int i);
void interrupt_enable(int i);

#endif