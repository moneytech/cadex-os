/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */
/**
 * A utility to encode and decode base64 strings
 */

#include <stdio.h>
#include <stdlib.h>
#include <sul/base64.h>
#include <unistd.h> 

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (!strcmp(argv[0], "--encode")) {
            char *arg1 = argv[1];
            char *input_str = arg1;
            int len_str;
            // calculates length of string
            len_str = sizeof(input_str) / sizeof(input_str[0]);
            printf("%s\n", base64_encode(input_str, len_str));
        } else {
            printf("base64: unknown option: %s", argv[0]);
        }
    } else {
        // print the usage if lengthOf(argc < 0)
        printf("usage: base64 [--encode|decode] <string> ");
    }
    return 0;
}
