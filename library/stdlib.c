#include <kernel/gfxstream.h>
#include <kernel/types.h>
#include <library/stdio.h>
#include <library/syscalls.h>
#include <library/string.h>
#include <library/stdbool.h>
#include <library/math.h>
#include <library/assert.h>
#include "stdarg.h"

// Executes specified file with specified argc and argv.
// int system(string *program, int argc, string **argv)
// {
//     syscall_process_exec(program, argc, argv);
//     return false;
// }
// ^^^^^ -> Commented because it is defined in stdio.c