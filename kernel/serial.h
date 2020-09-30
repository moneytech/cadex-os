/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef SERIAL_H
#define SERIAL_H

void serial_init();

char serial_read(uint8_t port_no);
int serial_write(uint8_t port_no, char a);

int serial_device_probe( int unit, int *blocksize, int *nblocks, char *info );
int serial_device_read( int unit, void *data, int length, int offset );
int serial_device_write( int unit, const void *data, int length, int offset );

#endif
