/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef SERIAL_H
#define SERIAL_H

#include "ioports.h"

#define COM1 0x3f8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void serial_init();

char serial_read(uint8_t port_no);
int serial_write(uint8_t port_no, char a);

int serial_device_probe(int unit, int *blocksize, int *nblocks, char *info);
int serial_device_read(int unit, void *data, int length, int offset);
int serial_device_write(int unit, const void *data, int length, int offset);

#endif
