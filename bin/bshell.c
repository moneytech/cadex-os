/**
 * bshell - A simple Cadex BASIC/BASIC86 shell
 *
 *
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
 */

#include <auth.h>
#include <library/math.h>
#include <library/scanf.h>
#include <library/stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_INPUT_CHARS 1024
#define pass            continue

typedef int keyword_t;

/**
 * !HELPER FUNCTIONS
 */
int check_semicolon(char *string[]) { return strEndsWith(string, ";"); }
int check_colon(char *string[]) { return strEndsWith(string, ":"); }
int is_annotation(char *string[]) { return strStartsWith("@", string); }
int is_comment(char *string[]) { return strStartsWith("-", string); }
int check_keyword(char *string, const char *keyword) {
    return !strcmp(string, keyword);
}

/**
 * !KEYWORD HANDLERS
 */
keyword_t print_function(int argc, char *argv[]) {
    if (argc > 0)
    {
        printf(argv[0]);
    }
}

int main(int argc, char *argv[]) {
    char *cargv[100];
    int cargc;
    int scargv;
    char *input[MAX_INPUT_CHARS];
    char *pre_prompt_str = "";

    printf("BASIC Commander v1.0\n");
    printf(
        "Type HELP for a list of commands or EXIT for exiting the commander\n");
    while (1) {
        // printf("%s> ", pre_prompt_str);
        scanf(input, sizeof(input));
        // Number of arguments
        cargc = 0;
        // LEXER!!!
        // This is similar to cargv.split(" ") in JavaScript
        cargv[cargc] = strtok(input, " ");
        while (cargv[cargc]) {
            cargc++;
            cargv[cargc] = strtok(0, " ");
        }
        if (cargc > 0) {
            if (check_keyword(cargv[0], "print")) {
                print_function(cargc - 1, &argv);
            } else {
                printf("?SYNTAX ERROR\n");
            }
        }
    }
    // return 0;
}
