/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * uname: Utility to view Kernel name, version, and codename
 */
#include <library/version.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    if (argc > 0) {
        if (!strcmp(argv[0], "-a")) {
            printf("CadexOS version %s Codename \"%s\"\nKernel architecture: "
                   "%s\nKernel build date: %s\nKernel build Time: %s\n",
                   _LTS_REL_, _K_CODENAME, _K_ARCH, __K_BUILD_DATE,
                   __K_BUILD_TIME);
        } else if (!strcmp(argv[0], "-v")) {
            printf("%s-%s\n", _LTS_REL_, __VER_SUFFIX);
        } else {
            printf("Usage:\nuname [options]\nOptions:\n * -a: Display a string "
                   "of OS version, codename, name, build, type and "
                   "architecture\n * -v: Display OS version");
        }
    }
    return 0;
}
