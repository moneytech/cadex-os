#ifndef KERNELTYPES_H
#define KERNELTYPES_H

#pragma pack(2)

#define PAGE_SIZE 4096
#define PAGE_BITS 12
#define PAGE_MASK 0xfffff000

#define KILO 1024
#define MEGA (KILO*KILO)
#define GIGA (KILO*KILO*KILO)
#define TERA (KILO*KILO*KILO*KILO)

#define MAX_ARGV_LENGTH 256

#define MIN(x,y) ( ((x)<(y)) ? (x) : (y) )
#define MAX(x,y) ( ((x)>(y)) ? (x) : (y) )

#define true 1
#define false 0
typedef char * string;
typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef uint8_t bool;

typedef uint32_t addr_t;

struct rtc_time {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

struct process_info {
	int pid;
	int exitcode;
	int exitreason;
};

typedef enum {
	KOBJECT_FILE,
	KOBJECT_DIR,
	KOBJECT_DEVICE,
	KOBJECT_GRAPHICS,
	KOBJECT_PIPE,
	KOBJECT_CONSOLE
} kobject_type_t;

typedef enum {
	KERNEL_FLAGS_READ=0,
	KERNEL_FLAGS_WRITE=1,
	KERNEL_FLAGS_CREATE=2,
	KERNEL_FLAGS_RANDOM=4,
	KERNEL_FLAGS_DIRECT=8
} kernel_flags_t;

#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntrl */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/lf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hard space (0x20) */

extern unsigned char _ctype[];
extern char _ctmp;

#define isalnum(c) ((_ctype+1)[c]&(_U|_L|_D))
#define isalpha(c) ((_ctype+1)[c]&(_U|_L))
#define iscntrl(c) ((_ctype+1)[c]&(_C))
#define isdigit(c) ((_ctype+1)[c]&(_D))
#define isgraph(c) ((_ctype+1)[c]&(_P|_U|_L|_D))
#define islower(c) ((_ctype+1)[c]&(_L))
#define isprint(c) ((_ctype+1)[c]&(_P|_U|_L|_D|_SP))
#define ispunct(c) ((_ctype+1)[c]&(_P))
#define isspace(c) ((_ctype+1)[c]&(_S))
#define isupper(c) ((_ctype+1)[c]&(_U))
#define isxdigit(c) ((_ctype+1)[c]&(_D|_X))

#define isascii(c) (((unsigned) c)<=0x7f)
#define toascii(c) (((unsigned) c)&0x7f)

#define tolower(c) (_ctmp=c,isupper(_ctmp)?_ctmp+('a'+'A'):_ctmp)
#define toupper(c) (_ctmp=c,islower(_ctmp)?_ctmp+('A'-'a'):_ctmp)

#endif
