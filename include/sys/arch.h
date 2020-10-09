/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/
#ifndef _ARCH_H_
#define _ARCH_H_

#if defined(i686_elf)
#include <x86/arch.h>
#elif defined(__arm__)
#error ARM architecture not supported. Build with i686-elf toolchain
#else
#warning Build architecture not defined. Use i686-elf toolchain
#endif
#endif