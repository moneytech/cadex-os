/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */


/*
This module is the runtime start of every user-level program.
The very first symbol in this module must be _start() because
the kernel simply jumps to the very first location of the executable.
_start() sets up any necessary runtime environment and invokes
the main function.  Note that this function cannot exit, but
must invoke the _process_exit() function to terminate the process.
*/

void _init();
void _fini();
#include "library/syscalls.h"
int main(int argc, const char *argv[]);
const char **environ = {"PATH=/bin/,/usr/bin,/sys"};
__attribute__((__noreturn__)) void _start(int argc, const char **argv) { _process_exit(main(argc, argv)); }
