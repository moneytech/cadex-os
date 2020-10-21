/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef STRING_H
#define STRING_H

#include <library/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define COS_SOURCE

void strcpy(char *d, const char *s);
void strncpy(char *d, const char *s, unsigned length);
char *strdup(const char *s);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, unsigned length);
char *strdup(const char *s);
unsigned strlen(const char *s);
char *strcat(char *d, const char *s);
char *uint_to_string(uint32_t u, char *str);
char *strrev(char *s);
char *strtok(char *s, const char *delim);
int str2int(const char *s, int *d);
const char *strchr(const char *s, char ch);
int memset(void *d, char value, unsigned length);
void memcpy(void *d, const void *s, unsigned length);
int printf(const char *s, ...);
void printf_putstring(char *str);
void reverseSentence();
int strEndsWith(const char *str, const char *suffix);
int strStartsWith(const char *pre, const char *str);
void itoa(int num, char *number);
#ifdef __cplusplus
}
#endif
#endif
