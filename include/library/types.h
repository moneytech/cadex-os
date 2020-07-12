#ifndef TYPES_H
#define TYPES_H

#pragma pack(2)

typedef char *string;
typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

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

extern unsigned char _ctype[];
extern char _ctmp;

#define _isalnum(c) ((_ctype+1)[c]&(_U|_L|_D))
#define _isalpha(c) ((_ctype+1)[c]&(_U|_L))
#define _iscntrl(c) ((_ctype+1)[c]&(_C))
#define _isdigit(c) ((_ctype+1)[c]&(_D))
#define _isgraph(c) ((_ctype+1)[c]&(_P|_U|_L|_D))
#define _islower(c) ((_ctype+1)[c]&(_L))
#define _isprint(c) ((_ctype+1)[c]&(_P|_U|_L|_D|_SP))
#define _ispunct(c) ((_ctype+1)[c]&(_P))
#define _isspace(c) ((_ctype+1)[c]&(_S))
#define _isupper(c) ((_ctype+1)[c]&(_U))
#define _isxdigit(c) ((_ctype+1)[c]&(_D|_X))

#define _isascii(c) (((unsigned) c)<=0x7f)
#define _toascii(c) (((unsigned) c)&0x7f)

#define _tolower(c) (_ctmp=c,isupper(_ctmp)?_ctmp+('a'+'A'):_ctmp)
#define _toupper(c) (_ctmp=c,islower(_ctmp)?_ctmp+('A'-'a'):_ctmp)

#endif
