/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#ifndef LIBRARY_STDLIB_H
#define LIBRARY_STDLIB_H
#pragma once

#include <library/_cheader.h>
#include <library/stddef.h>
#include <library/types.h>

_Begin_C_Header

    extern void
    exit(int status);
extern char* getenv(const char* name);
extern char* getenvpath();
// extern void *malloc(size_t size);
// extern void free(void *ptr);
// extern void *calloc(size_t nmemb, size_t size);
// extern void *realloc(void *ptr, size_t size);

extern void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

//extern int exec(char *, int, char **, char **, int);
//extern int system(char *, int, char **, char **);

// extern int abs(int j);

extern int putenv(char* name);
extern int setenv(const char* name, const char* value, int overwrite);
extern int unsetenv(const char* str);

extern double strtod(const char* nptr, char** endptr);

#define ATEXIT_MAX 32
extern int atexit(void (*h)(void));
extern void _handle_atexit(void);

#define RAND_MAX 0x7FFFFFFF

extern void abort(void);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int atoi(const char*);
long atol(const char*);
long long atoll(const char*);
double atof(const char*);

float strtof(const char* __restrict, char** __restrict);
double strtod(const char* __restrict, char** __restrict);
long double strtold(const char* __restrict, char** __restrict);
int abs(int);
long labs(long);
long long llabs(long long);
long strtol(const char* __restrict, char** __restrict, int);
unsigned long strtoul(const char* __restrict, char** __restrict, int);
long long strtoll(const char* __restrict, char** __restrict, int);
unsigned long long strtoull(const char* __restrict, char** __restrict, int);

extern void* bsearch(const void* key, const void* base, size_t nmemb, size_t size,
    int (*compar)(const void*, const void*));

extern char* mktemp(char*);
extern int mkstemp(char*);

extern size_t mbstowcs(wchar_t* dest, const char* src, size_t n);
extern size_t wcstombs(char* dest, const wchar_t* src, size_t n);

typedef struct
{
    int quot;
    int rem;
} div_t;
typedef struct
{
    long int quot;
    long int rem;
} ldiv_t;

typedef struct
{
    long long quot, rem;
} lldiv_t;
#define WNOHANG 1
#define WUNTRACED 2

#define WEXITSTATUS(s) (((s)&0xff00) >> 8)
#define WTERMSIG(s) ((s)&0x7f)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSTOPPED(s) ((short)((((s)&0xffff) * 0x10001) >> 8) > 0x7f00)
#define WIFSIGNALED(s) (((s)&0xffff) - 1U < 0xffu)
int posix_memalign(void**, size_t, size_t);
int mkstemp(char*);
int mkostemp(char*, int);
char* mkdtemp(char*);
int getsubopt(char**, char* const*, char**);
uint32_t rand(uint32_t min, uint32_t max);
void srand(unsigned int seed);

extern div_t div(int numerator, int denominator);
extern ldiv_t ldiv(long numerator, long denominator);

/* These are supposed to be in limits, but gcc screwed us */
#define PATH_MAX 4096
#define NAME_MAX 255
extern char* realpath(const char* path, char* resolved_path);

// PANIC function
extern void PANIC(char* sender, char* str);
_End_C_Header
#endif
