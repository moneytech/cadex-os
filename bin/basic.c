/**
 * basic - A simple Cadex BASIC/BASIC86 interpreter
 * 
 *
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <stdio.h>
#include <library/scanf.h>
#include <auth.h>
#include <library/string.h>

#define MAX_INPUT_CHARS 1024

int check_semicolon(char *string[])
{
    return strEndsWith(string, ";");
}
int check_colon(char *string[])
{
    return strEndsWith(string, ":");
}
int is_annotation(char *string[])
{
    return strStartsWith("@", string);
}
int is_comment(char *string[])
{
    return strStartsWith("-", string);
}
int main(int argc, const char *argv[])
{
    char *cargv[100];
    int cargc;
    int scargv;
    char *input[MAX_INPUT_CHARS];
    int basic_is;
    int assembly = 0;
    int asyncmethod = 0;
    syscall_chdir("/");
    int dir_fd = syscall_open_file("/", 0, 0);
    // syscall_object_set_tag(dir_fd, "ROOT");
    // printf("Opened root directory\n");
    int fd = syscall_open_file(argv[0], 0, 0);
    char buffer[1000];
    int n;
    //printf("reading file...\n");
    setTextColor(0, 200, 0, 100);
    resetColor();
    if (strEndsWith(argv[0], ".b86"))
    {
        printf("FILE: %s\n\n", argv[0]);
        while ((n = fgets(fd, buffer, 100)) > 0)
        {
            buffer[n] = 0;

            cargc = 0;
            // LEXER!!!
            // This is similar to cargv.split(" ") in JavaScript
            cargv[cargc] = strtok(buffer, " ");
            while (cargv[cargc])
            {
                cargc++;
                cargv[cargc] = strtok(0, " ");
            }
            if (cargc > 0)
            {
                if (!strcmp(cargv[0], "print_help"))
                {
                    printf("List of available commands:\n");
                    printf(" * PRINT: Prints text to the screen\n");
                    printf(" * EXIT: Exits the commander\n");
                    printf(" * END: Ends the current command input stream\n");
                    printf(" * CLS: Clears the screen\n");
                    printf(" * EXECUTE: Executes the specified file\n");
                    printf(" * CMDREGISTER: Adds a new command to the command list. [NOTE: This commander can only store one custom command]\n");
                    printf("\nList of available Annotations (Attributes):\n");
                    printf(" * @ASM86: Enables x86 Assembly input mode\n");
                    printf(" * @END_ASM86: Disables x86 Assembly input mode\n");
                    printf(" * @CMD: Enables command definition mode\n");
                    printf(" * @END_CMD: Disables command definition mode\n");
                }
                else if (is_comment(cargv[0]))
                {
                    continue;
                }

                else if (!strcmp(cargv[0], "exit"))
                {
                    _process_exit(0);
                    return 0;
                }
                else if (!strcmp(cargv[0], "print:"))
                {
                    scargv = cargc;
                    for (size_t i = 1; i < scargv; i++)
                    {
                        if (!strcmp(cargv[i], ":end"))
                        {
                            break;
                        }
                        else
                        {
                            printf("%s ", cargv[i]);
                        }
                    }
                    printf("\n");
                }

                else if (!strcmp(cargv[0], "@ASM86"))
                {
                    printf("[INFO] Assembly mode enabled\n");
                    assembly = 1;
                }
                else if (!strcmp(cargv[0], "@END_ASM86"))
                {
                    assembly = 0;
                }
                else if (!strcmp(cargv[0], "mov"))
                {
                    if (assembly)
                    {
                    }
                    else
                    {
                        printf("[ERR] Assembly mode is not enabled.");
                    }
                }

                else if (!strcmp(cargv[0], "cls"))
                {
                    int x1 = 12;
                    int y1 = 12;
                    int dims[2];
                    char stop = -1;
                    int i = 0;
                    syscall_object_size(WN_STDWINDOW, dims, 2);

                    int width = dims[0];
                    int height = dims[1];

                    renderWindow(WN_STDWINDOW);
                    clearScreen(0, 0, width, height);
                    flushScreen();
                    flush();
                }
                else if (!strcmp(cargv[0], "cmdregister"))
                {
                    /* code */
                }

                else if (!strcmp(cargv[0], "execute:"))
                {
                    int pid = fork();

                    if (pid == 0)
                    {
                        printf("Process %d started.\n", syscall_process_self());
                        const char *args[] = {cargv[1]};
                        system(cargv[1], 1, args);
                    }
                    else
                    {
                        //printf("hello world, I am the parent %d.\n", syscall_process_self());
                        struct process_info info;
                        syscall_process_wait(&info, -1);
                        syscall_process_reap(info.pid);
                    }
                }
                else
                {
                    printf("[ERR] Syntax error: no command named '%s' exists in the current instance\n", cargv[0]);
                }
            }
        }
    }
    else
    {
        printf("Error: Specified file does not have '.b86' file extension. Cadex BASIC files must have '.b86' file extension.\n");
        _process_exit(0);
        return 0;
    }
    return 0;
}