/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/
/**
 * Standatd types for userspace libraries
*/

#ifndef TYPES_H
#define TYPES_H

#pragma pack(2)

typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

typedef long off_t;
typedef long time_t;

typedef int gid_t;
typedef int uid_t;
typedef int dev_t;
typedef int ino_t;
typedef int mode_t;
typedef int caddr_t;

typedef unsigned long useconds_t;
typedef long suseconds_t;
typedef int pid_t;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef uint32_t addr_t;

struct rtc_time_t {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

struct process_info_t {
	int pid;
	int exitcode;
	int exitreason;
};


#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntrl */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/lf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hard space (0x20) */
#define false 0
#define true 1

#endif
