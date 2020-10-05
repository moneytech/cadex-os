/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * This is where the starting point of every C++ applications are defined.
 * This is a bit weird to use a single C++ file in between the C library
*/
 
#include "library/syscalls.h"
#include <sys/rt/cxxrt0.hpp>

int main(int argc, const char *argv[]);

void _start(int argc, const char **argv)
{
    __cxa_finalize(NULL);
    _process_exit(main(argc, argv));
}
