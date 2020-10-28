#ifndef KERNELTYPES_H
#define KERNELTYPES_H

//#pragma pack(2)

#include "kernel/stdbool.h"

// Pagetable defines
#define PAGE_SIZE 4096
#define PAGE_BITS 12
#define PAGE_MASK 0xfffff000

// Data unit defines
#define KILO 1024
#define MEGA (KILO * KILO)
#define GIGA (KILO * KILO * KILO)
#define TERA (KILO * KILO * KILO * KILO)

// Maximum command line arguments passed to an application
#define MAX_ARGV_LENGTH 256

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// Null type in C is (void*)0 and in C++ it is nullptr
#ifndef NULL
#    define NULL (void*)0
#endif

// Check if false is not defined (C doesn't have booleans by default)
#ifndef false
#    define false 0
#endif

// Used by some drivers
#ifndef FALSE
#    define FALSE 0
#endif

// Check if true is not defined (C doesn't have booleans by default)
#ifndef true
#    define true 1
#endif

// Used by some drivers
#ifndef TRUE
#    define TRUE 1
#endif

// We are using a non-gnu standard
#define asm __asm__
#define volatile __volatile__

// BOOL is generally declared in windows.h (This isn't windows, that's why we are #defining it
#ifndef BOOL
#    define BOOL int
#endif // !BOOL

// Signed types
typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

// Unsigned types
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef uint32_t addr_t;

// Used by RTC driver
struct rtc_time {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

// Stubbed
struct process_info {
    int pid;
    int exitcode;
    int exitreason;
};

// Kernel object enum type definition
typedef enum {
    KOBJECT_FILE,
    KOBJECT_DIR,
    KOBJECT_DEVICE,
    KOBJECT_GRAPHICS,
    KOBJECT_PIPE,
    KOBJECT_CONSOLE
} kobject_type_t;

// Kernel flags enum type definition
typedef enum {
    KERNEL_FLAGS_READ = 0,
    KERNEL_FLAGS_WRITE = 1,
    KERNEL_FLAGS_CREATE = 2,
    KERNEL_FLAGS_RANDOM = 4,
    KERNEL_FLAGS_DIRECT = 8
} kernel_flags_t;

// Stubbed
struct timeval {
    uint32_t tv_sec;
    uint32_t tv_usec;
};

#endif
