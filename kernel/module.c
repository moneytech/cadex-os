/**
 * module.c: module-related functions
*/
#include "module.h"

extern void module_load(const char *name, uint8_t *elf)
{
    elf_sym_t *s[1];
    elf_sect_t *sect[1];
    module_init_callback_t c;

    kprintf("[MODULE] %s: ", name);

    if (elf32_check(elf, ET_DYN) == FALSE)
    {
        kprintf("invalid MO file\n");
        return;
    }

    if (elf32_search_symbol(elf, "_start", -1, s))
    {
        kprintf("init @ 0x%x ", (uint32_t)elf + s[0]->value);
        c = (module_init_callback_t)((uint32_t)elf + s[0]->value);
        // c();
    }
    // test module
    if (elf32_search_symbol(elf, "foo", -1, s))
    {
        if (elf32_get_section_i(elf, s[0]->section, sect))
        {
            kprintf("foo (0x%x): %s ", (uint32_t)(sect[0]->offset + s[0]->value + (uint32_t)elf), (uint8_t *)(sect[0]->offset + s[0]->value + (uint32_t)elf));
        }
    }

    kprintf("loaded.\n");
}
