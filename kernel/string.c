/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "string.h"
#include "kernel/types.h"
#include "kernel/ascii.h"
#include "kmalloc.h"

//#include "stdarg.h"
#include "console.h"

#define _U 0x01	 /* upper */
#define _L 0x02	 /* lower */
#define _D 0x04	 /* digit */
#define _C 0x08	 /* cntrl */
#define _P 0x10	 /* punct */
#define _S 0x20	 /* white space (space/lf/tab) */
#define _X 0x40	 /* hex digit */
#define _SP 0x80 /* hard space (0x20) */

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1 / UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(X) (((X)-ONES) & ~(X)&HIGHS)
unsigned char chartmp[];
char _ctmp;

#define isalnum(c) ((chartmp + 1)[c] & (_U | _L | _D))
#define isalpha(c) ((chartmp + 1)[c] & (_U | _L))
#define iscntrl(c) ((chartmp + 1)[c] & (_C))
#define isdigit(c) ((chartmp + 1)[c] & (_D))
#define isgraph(c) ((chartmp + 1)[c] & (_P | _U | _L | _D))
#define islower(c) ((chartmp + 1)[c] & (_L))
#define isprint(c) ((chartmp + 1)[c] & (_P | _U | _L | _D | _SP))
#define ispunct(c) ((chartmp + 1)[c] & (_P))
#define isspace(c) ((chartmp + 1)[c] & (_S))
#define isupper(c) ((chartmp + 1)[c] & (_U))
#define isxdigit(c) ((chartmp + 1)[c] & (_D | _X))

#define isascii(c) (((unsigned)c) <= 0x7f)
#define toascii(c) (((unsigned)c) & 0x7f)

#define tolower(c) (_ctmp = c, isupper(_ctmp) ? _ctmp + ('a' + 'A') : _ctmp)
#define toupper(c) (_ctmp = c, islower(_ctmp) ? _ctmp + ('A' - 'a') : _ctmp)

#define BITOP(A, B, OP) \
	((A)[(size_t)(B) / (8 * sizeof *(A))] OP(size_t) 1 << ((size_t)(B) % (8 * sizeof *(A))))

void strcpy(char *d, const char *s)
{
	while(*s) {
		*d++ = *s++;
	}
	*d = 0;
}

void strncpy(char *d, const char *s, unsigned length)
{
	while(*s && length--) {
		*d++ = *s++;
	}
	*d = 0;
}

int strcmp(const char *a, const char *b)
{
	while(1) {
		if(*a < *b) {
			return -1;
		} else if(*a > *b) {
			return 1;
		} else if(*a == 0) {
			return 0;
		} else {
			a++;
			b++;
		}
	}
}

int strncmp(const char *a, const char *b, unsigned length)
{
	while(length > 0) {
		if(*a < *b) {
			return -1;
		} else if(*a > *b) {
			return 1;
		} else if(*a == 0) {
			return 0;
		} else {
			a++;
			b++;
			length--;
		}
	}
	return 0;
}

unsigned strlen(const char *s)
{
	unsigned len = 0;
	while(*s) {
		len++;
		s++;
	}
	return len;
}

char *strrev(char *s)
{
	unsigned start = 0;
	unsigned end = strlen(s) - 1;
	char swap;

	while(start < end) {
		swap = s[start];
		s[start] = s[end];
		s[end] = swap;

		start++;
		end--;
	}

	return s;
}

char *strcat(char *d, const char *s)
{
	strcpy(d + strlen(d), s);
	return d;
}

const char *strchr(const char *s, char ch)
{
	while(*s) {
		if(*s == ch)
			return s;
		s++;
	}
	return 0;
}

char *strtok(char *s, const char *delim)
{
	static char *oldword = 0;
	char *word;

	if(!s)
		s = oldword;

	while(*s && strchr(delim, *s))
		s++;

	if(!*s) {
		oldword = s;
		return 0;
	}

	word = s;
	while(*s && !strchr(delim, *s))
		s++;

	if(*s) {
		*s = 0;
		oldword = s + 1;
	} else {
		oldword = s;
	}

	return word;
}

char *strdup(const char *s)
{
	char *new = kmalloc(strlen(s) + 1);
	if(new)
		strcpy(new, s);
	return new;
}

char *strndup(const char *s, unsigned length)
{
	char *new = kmalloc(length+1);
	if(new) {
		strncpy(new,s,length);
		new[length] = 0;
	}
	return new;
}

void strtoupper(char *name)
{
	while(*name) {
		if(*name >= 'a' && *name <= 'z') {
			*name -= 'a' - 'A';
		}
		name++;
	}
}

void strtolower(char *name)
{
	while(*name) {
		if(*name >= 'A' && *name <= 'Z') {
			*name += 'a' - 'A';
		}
		name++;
	}
}

int str2int(const char *s, int *d)
{
	int val = 0;
	for(; *s; ++s) {
		val *= 10;
		if(*s > ASCII_9 || *s < ASCII_0) {
			return 0;
		}
		val += (*s - '0');
	}
	*d = val;
	return 1;
}

void memset(void *vd, char value, unsigned length)
{
	char *d = vd;
	while(length) {
		*d = value;
		length--;
		d++;
	}
}

void memcpy(void *vd, const void *vs, unsigned length)
{
	char *d = vd;
	const char *s = vs;
	while(length) {
		*d = *s;
		d++;
		s++;
		length--;
	}
}

char *uint_to_string(uint32_t u, char *s)
{
	uint32_t f, d, i;

	f = 1;
	i = 0;
	while((u / (f * 10)) > 0) {
		f *= 10;
	}
	while(f > 0) {
		d = u / f;
		s[i] = '0' + d;
		u = u % f;
		f = f / 10;
		i++;
	}
	s[i] = 0;
	return s;
}
int atoi(const char *s)
{
	int n = 0;
	int neg = 0;
	while (isspace(*s))
	{
		s++;
	}
	switch (*s)
	{
	case '-':
		neg = 1;
		/* Fallthrough is intentional here */
	case '+':
		s++;
	}
	while (isdigit(*s))
	{
		n = 10 * n - (*s++ - '0');
	}
	/* The sign order may look incorrect here but this is correct as n is calculated
	 * as a negative number to avoid overflow on INT_MAX.
	 */
	return neg ? n : -n;
}

static uint32_t digit_count(int num)
{
	uint32_t count = 0;
	if (num == 0)
		return 1;
	while (num > 0)
	{
		count++;
		num = num / 10;
	}
	return count;
}

void itoa(int num, char *number)
{
	int dgcount = digit_count(num);
	int index = dgcount - 1;
	char x;
	if (num == 0 && dgcount == 1)
	{
		number[0] = '0';
		number[1] = '\0';
	}
	else
	{
		while (num != 0)
		{
			x = num % 10;
			number[index] = x + '0';
			index--;
			num = num / 10;
		}
		number[dgcount] = '\0';
	}
}
