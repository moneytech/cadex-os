/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */
/**
 * Brainkick - A simple programming language
 */

#include <stdio.h>

#define BASIC_ADD "+++-"

void interpret(char *program) {
    char *ipc = program;
    int counter;

    while (*ipc) {
        if (*ipc == '*') {
            return;
        } else if (*ipc == '^') {
            counter = 0;
        } else if (*ipc == '&') {
            if (counter)
                counter = 0;
            else
                counter = 1;
        }

        else if (*ipc == '+') {
            counter++;
        } else if (*ipc == '-') {
            counter--;
        } else if (*ipc == '>') {
            printf("%d\n", counter);
        }

        *ipc++;
    }
}

int main(int argc, char const *argv[]) {
    char *prg;
    if (argc > 0) {
        interpret(argv[0]);
    }
    return 0;
}
