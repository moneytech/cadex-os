/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include <kernel/types.h>
#include <kernel/ascii.h>
#include <library/malloc.h>
#include <library/string.h>
#include <library/syscalls.h>
#include <library/malloc.h>
#include <library/stdarg.h>
#include <library/stdlib.h>
#include <library/list_t.h>
#include <library/assert.h>
#include <library/color.h>
#include <library/errno.h>
#include <library/stdint.h>
#include <library/float.h>
#include <library/list_t.h>
#include <library/strtoui.h>
#include <library/_cheader.h>
#include <library/stdio.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1 / UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(X) (((X)-ONES) & ~(X)&HIGHS)

#define BITOP(A, B, OP) \
	((A)[(size_t)(B) / (8 * sizeof *(A))] OP(size_t) 1 << ((size_t)(B) % (8 * sizeof *(A))))

void strcpy(char *d, const char *s)
{
	while (*s)
	{
		*d++ = *s++;
	}
	*d = 0;
}
size_t strspn(const char *s, const char *c)
{
	const char *a = s;
	size_t byteset[32 / sizeof(size_t)] = {0};

	if (!c[0])
	{
		return 0;
	}
	if (!c[1])
	{
		for (; *s == *c; s++)
			;
		return s - a;
	}

	for (; *c && BITOP(byteset, *(unsigned char *)c, |=); c++)
		;
	for (; *s && BITOP(byteset, *(unsigned char *)s, &); s++)
		;

	return s - a;
}

char *strchrnul(const char *s, int c)
{
	size_t *w;
	size_t k;

	c = (unsigned char)c;
	if (!c)
	{
		return (char *)s + strlen(s);
	}

	for (; (uintptr_t)s % ALIGN; s++)
	{
		if (!*s || *(unsigned char *)s == c)
		{
			return (char *)s;
		}
	}

	k = ONES * c;
	for (w = (void *)s; !HASZERO(*w) && !HASZERO(*w ^ k); w++)
		;
	for (s = (void *)w; *s && *(unsigned char *)s != c; s++)
		;
	return (char *)s;
}

// char *strchr(const char *s, int c)
// {
	// char *r = strchrnul(s, c);
	// return *(unsigned char *)r == (unsigned char)c ? r : 0;
// }

// char *strrchr(const char *s, int c)
// {
// 	return memrchr(s, c, strlen(s) + 1);
// }

size_t strcspn(const char *s, const char *c)
{
	const char *a = s;
	if (c[0] && c[1])
	{
		size_t byteset[32 / sizeof(size_t)] = {0};
		for (; *c && BITOP(byteset, *(unsigned char *)c, |=); c++)
			;
		for (; *s && !BITOP(byteset, *(unsigned char *)s, &); s++)
			;
		return s - a;
	}
	return strchrnul(s, *c) - a;
}

char *strpbrk(const char *s, const char *b)
{
	s += strcspn(s, b);
	return *s ? (char *)s : 0;
}

static char *strstr_2b(const unsigned char *h, const unsigned char *n)
{
	uint16_t nw = n[0] << 8 | n[1];
	uint16_t hw = h[0] << 8 | h[1];
	for (h++; *h && hw != nw; hw = hw << 8 | *++h)
		;
	return *h ? (char *)h - 1 : 0;
}

static char *strstr_3b(const unsigned char *h, const unsigned char *n)
{
	uint32_t nw = n[0] << 24 | n[1] << 16 | n[2] << 8;
	uint32_t hw = h[0] << 24 | h[1] << 16 | h[2] << 8;
	for (h += 2; *h && hw != nw; hw = (hw | *++h) << 8)
		;
	return *h ? (char *)h - 2 : 0;
}

static char *strstr_4b(const unsigned char *h, const unsigned char *n)
{
	uint32_t nw = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	uint32_t hw = h[0] << 24 | h[1] << 16 | h[2] << 8 | h[3];
	for (h += 3; *h && hw != nw; hw = hw << 8 | *++h)
		;
	return *h ? (char *)h - 3 : 0;
}

// static char *strstr_twoway(const unsigned char *h, const unsigned char *n)
// {
// 	size_t mem;
// 	size_t mem0;
// 	size_t byteset[32 / sizeof(size_t)] = {0};
// 	size_t shift[256];
// 	size_t l;

// 	/* Computing length of needle and fill shift table */
// 	for (l = 0; n[l] && h[l]; l++)
// 	{
// 		BITOP(byteset, n[l], |=);
// 		shift[n[l]] = l + 1;
// 	}

// 	if (n[l])
// 	{
// 		return 0; /* hit the end of h */
// 	}

// 	/* Compute maximal suffix */
// 	size_t ip = -1;
// 	size_t jp = 0;
// 	size_t k = 1;
// 	size_t p = 1;
// 	while (jp + k < l)
// 	{
// 		if (n[ip + k] == n[jp + k])
// 		{
// 			if (k == p)
// 			{
// 				jp += p;
// 				k = 1;
// 			}
// 			else
// 			{
// 				k++;
// 			}
// 		}
// 		else if (n[ip + k] > n[jp + k])
// 		{
// 			jp += k;
// 			k = 1;
// 			p = jp - ip;
// 		}
// 		else
// 		{
// 			ip = jp++;
// 			k = p = 1;
// 		}
// 	}
// 	size_t ms = ip;
// 	size_t p0 = p;

// 	/* And with the opposite comparison */
// 	ip = -1;
// 	jp = 0;
// 	k = p = 1;
// 	while (jp + k < l)
// 	{
// 		if (n[ip + k] == n[jp + k])
// 		{
// 			if (k == p)
// 			{
// 				jp += p;
// 				k = 1;
// 			}
// 			else
// 			{
// 				k++;
// 			}
// 		}
// 		else if (n[ip + k] < n[jp + k])
// 		{
// 			jp += k;
// 			k = 1;
// 			p = jp - ip;
// 		}
// 		else
// 		{
// 			ip = jp++;
// 			k = p = 1;
// 		}
// 	}
// 	if (ip + 1 > ms + 1)
// 	{
// 		ms = ip;
// 	}
// 	else
// 	{
// 		p = p0;
// 	}

// 	/* Periodic needle? */
// 	if (memcmp(n, n + p, ms + 1))
// 	{
// 		mem0 = 0;
// 		p = MAX(ms, l - ms - 1) + 1;
// 	}
// 	else
// 	{
// 		mem0 = l - p;
// 	}
// 	mem = 0;

// 	/* Initialize incremental end-of-haystack pointer */
// 	const unsigned char *z = h;

// 	/* Search loop */
// 	for (;;)
// 	{
// 		/* Update incremental end-of-haystack pointer */
// 		if ((size_t)(z - h) < l)
// 		{
// 			/* Fast estimate for MIN(l,63) */
// 			size_t grow = l | 63;
// 			const unsigned char *z2 = memchr(z, 0, grow);
// 			if (z2)
// 			{
// 				z = z2;
// 				if ((size_t)(z - h) < l)
// 				{
// 					return 0;
// 				}
// 			}
// 			else
// 			{
// 				z += grow;
// 			}
// 		}

// 		/* Check last byte first; advance by shift on mismatch */
// 		if (BITOP(byteset, h[l - 1], &))
// 		{
// 			k = l - shift[h[l - 1]];
// 			if (k)
// 			{
// 				if (mem0 && mem && k < p)
// 					k = l - p;
// 				h += k;
// 				mem = 0;
// 				continue;
// 			}
// 		}
// 		else
// 		{
// 			h += l;
// 			mem = 0;
// 			continue;
// 		}

// 		/* Compare right half */
// 		for (k = MAX(ms + 1, mem); n[k] && n[k] == h[k]; k++)
// 			;
// 		if (n[k])
// 		{
// 			h += k - ms;
// 			mem = 0;
// 			continue;
// 		}
// 		/* Compare left half */
// 		for (k = ms + 1; k > mem && n[k - 1] == h[k - 1]; k--)
// 			;
// 		if (k <= mem)
// 		{
// 			return (char *)h;
// 		}
// 		h += p;
// 		mem = mem0;
// 	}
// }

// char *strstr(const char *h, const char *n)
// {
// 	/* Return immediately on empty needle */
// 	if (!n[0])
// 	{
// 		return (char *)h;
// 	}

// 	/* Use faster algorithms for short needles */
// 	h = strchr(h, *n);
// 	if (!h || !n[1])
// 	{
// 		return (char *)h;
// 	}

// 	if (!h[1])
// 		return 0;
// 	if (!n[2])
// 		return strstr_2b((void *)h, (void *)n);
// 	if (!h[2])
// 		return 0;
// 	if (!n[3])
// 		return strstr_3b((void *)h, (void *)n);
// 	if (!h[3])
// 		return 0;
// 	if (!n[4])
// 		return strstr_4b((void *)h, (void *)n);

// 	/* Two-way on large needles */
// 	return strstr_twoway((void *)h, (void *)n);
// }

// int atoi(const char *s)
// {
// 	int n = 0;
// 	int neg = 0;
// 	while (isspace(*s))
// 	{
// 		s++;
// 	}
// 	switch (*s)
// 	{
// 	case '-':
// 		neg = 1;
// 		/* Fallthrough is intentional here */
// 	case '+':
// 		s++;
// 	}
// 	while (isdigit(*s))
// 	{
// 		n = 10 * n - (*s++ - '0');
// 	}
// 	/* The sign order may look incorrect here but this is correct as n is calculated
// 	 * as a negative number to avoid overflow on INT_MAX.
// 	 */
// 	return neg ? n : -n;
// }

void strncpy(char *d, const char *s, unsigned length)
{
	while (*s && length--)
	{
		*d++ = *s++;
	}
	*d = 0;
}

char *strdup(const char *s)
{
	char *d = (char *)malloc((strlen(s) + 1) * sizeof(char));
	char *tmp = d;
	while (*s)
	{
		*tmp++ = *s++;
	}
	*tmp = 0;
	return d;
}

int strcmp(const char *a, const char *b)
{
	while (1)
	{
		if (*a < *b)
		{
			return -1;
		}
		else if (*a > *b)
		{
			return 1;
		}
		else if (*a == 0)
		{
			return 0;
		}
		else
		{
			a++;
			b++;
		}
	}
}

int strncmp(const char *a, const char *b, unsigned length)
{
	while (length > 0)
	{
		if (*a < *b)
		{
			return -1;
		}
		else if (*a > *b)
		{
			return 1;
		}
		else if (*a == 0)
		{
			return 0;
		}
		else
		{
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
	while (*s)
	{
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

	while (start < end)
	{
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
	while (*s)
	{
		if (*s == ch)
			return s;
		s++;
	}
	return 0;
}

char *strtok(char *s, const char *delim)
{
	static char *oldword = 0;
	char *word;

	if (!s)
		s = oldword;

	while (*s && strchr(delim, *s))
		s++;

	if (!*s)
	{
		oldword = s;
		return 0;
	}

	word = s;
	while (*s && !strchr(delim, *s))
		s++;

	if (*s)
	{
		*s = 0;
		oldword = s + 1;
	}
	else
	{
		oldword = s;
	}

	return word;
}

int str2int(const char *s, int *d)
{
	int val = 0;
	for (; *s; ++s)
	{
		val *= 10;
		if (*s > ASCII_9 || *s < ASCII_0)
		{
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
	while (length)
	{
		*d = value;
		length--;
		d++;
	}
}

void memcpy(void *vd, const void *vs, unsigned length)
{
	char *d = vd;
	const char *s = vs;
	while (length)
	{
		*d = *s;
		d++;
		s++;
		length--;
	}
}
int strcoll(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}
extern void printf_putstring(char *str);
extern void printf_putchar(char c);

static void printf_puthexdigit(uint8_t i)
{
	if (i < 10)
	{
		printf_putchar('0' + i);
	}
	else
	{
		printf_putchar('a' + i - 10);
	}
}

static void printf_puthex(uint32_t i)
{
	int j;
	for (j = 28; j >= 0; j = j - 4)
	{
		printf_puthexdigit((i >> j) & 0x0f);
	}
}

static void printf_putint(int32_t i)
{
	int f, d;
	if (i < 0 && i != 0)
	{
		printf_putchar('-');
		i = -i;
	}

	f = 1;
	while ((i / f) >= 10)
	{
		f *= 10;
	}
	while (f > 0)
	{
		d = i / f;
		printf_putchar('0' + d);
		i = i - d * f;
		f = f / 10;
	}
}

static void printf_putuint(uint32_t u)
{
	int f, d;
	f = 1;
	while ((u / f) >= 10)
	{
		f *= 10;
	}
	while (f > 0)
	{
		d = u / f;
		printf_putchar('0' + d);
		u = u - d * f;
		f = f / 10;
	}
}

void printf(const char *s, ...)
{
	va_list args;

	uint32_t u;
	int32_t i;
	char *str;

	va_start(args, s);

	while (*s)
	{
		if (*s != '%')
		{
			printf_putchar(*s);
		}
		else
		{
			s++;
			switch (*s)
			{
			case 'd':
				i = va_arg(args, int32_t);
				printf_putint(i);
				break;
			case 'u':
				u = va_arg(args, uint32_t);
				printf_putuint(u);
				break;
			case 'x':
				u = va_arg(args, uint32_t);
				printf_puthex(u);
				break;
			case 's':
				str = va_arg(args, char *);
				printf_putstring(str);
				break;
			case 'c':
				u = va_arg(args, int32_t);
				printf_putchar(u);
				break;
			case 0:
				return;
				break;
			default:
				printf_putchar(*s);
				break;
			}
		}
		s++;
	}
	va_end(args);
}

char *uint_to_string(uint32_t u, char *s)
{
	uint32_t f, d, i;

	f = 1;
	i = 0;
	while ((u / (f * 10)) > 0)
	{
		f *= 10;
	}
	while (f > 0)
	{
		d = u / f;
		s[i] = '0' + d;
		u = u % f;
		f = f / 10;
		i++;
	}
	s[i] = 0;
	return s;
}

// void reverseSentence() {
//     char c;
//     scanf("%c", &c);
//     if (c != '\n') {
//         reverseSentence();
//         printf("%c", c);
//     }
// }
/* Work in progress */
//int scanf(char *line)
//{	int i = 0;
//    while (i < (length - 1))
//    {
//        char c;		syscall_object_read(0, &line, sizeof(&line));
//        if (c == ASCII_CR)
//        {
//            line[i] = 0;
//            printf("\n");
//            return 1;
//        }
//        else if (c == ASCII_BS)
//        {
//            if (i > 0)
//            {
//                putchar(c);
//                i--;
//            }
//        }
//        else if (c >= 0x20 && c <= 0x7E)
//        {
//            putchar(c);
//            line[i] = c;
//            i++;
//        }
//    }
//    return 0;
//}
