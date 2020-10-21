#include <kernel/types.h>
#include "elf.h"

extern void module_load(const char *name, uint8_t *elf);

typedef struct module
{
    char name[64];

    struct module *next;
} module_t;
typedef void (*module_init_callback_t)();
