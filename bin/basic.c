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

int x, y, w, h, fd;
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
    fd = syscall_open_file(argv[0], 0, 0);
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
            start:
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
                if (!strcmp(cargv[0], "help"))
                {
                    printf("List of available commands:\n");
                    printf(" * PRINT: Prints text to the screen\n");
                    printf(" * INPUT: Gets input from the user and print the prompt if specified\n");
                    printf(" * EXIT: Exits the commander\n");
                    printf(" * END: Ends the current command input stream\n");
                    printf(" * CLS: Clears the screen\n");
                    printf(" * EXECUTE: Executes the specified file\n");
                    printf(" * CMDREGISTER: Adds a new command to the command list. [NOTE: This commander can only store one custom command]\n");
                    printf("\nList of available Annotations (Attributes):\n");
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
                        else if (!strcmp(cargv[i], "\\n"))
                        {
                            printf("\n");
                        }
                        else if (!strcmp(cargv[i], "\\t"))
                        {
                            printf("   ");
                        }
                        else if (!strcmp(cargv[i], "$RAND"))
                        {
                            printf("%d", rand(1, 10000));
                        }

                        else
                        {
                            printf("%s ", cargv[i]);
                            goto start;
                        }
                    }
                    printf("\n");
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
                    goto start;
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
                else if (!strcmp(cargv[0], "drawrect"))
                {
                    int dims[2];
                    syscall_object_size(WN_STDWINDOW, dims, 2);

                    int width = dims[0];
                    int height = dims[1];

                    renderWindow(WN_STDWINDOW);
                    //clearScreen(0, 0, width, height);
                    flush();
                    drawRect(x, y, atoi(cargv[1]), atoi(cargv[2]));
                    flush();
                    flushScreen();
                }
                else if (!strcmp(cargv[0], "setx"))
                {
                    if (cargc > 1)
                    {
                        x = atoi(cargv[1]);
                    }
                    else
                    {
                        printf("Syntax: setx <x>\n");
                    }
                }
                else if (!strcmp(cargv[0], "sety"))
                {
                    if (cargc > 1)
                    {
                        y = atoi(cargv[1]);
                    }
                    else
                    {
                        printf("Syntax: sety <y>\n");
                    }
                }
                else if (!strcmp(cargv[0], "setxy"))
                {
                    if (cargc > 2)
                    {
                        x = atoi(cargv[1]);
                        y = atoi(cargv[2]);
                    }
                    else
                    {
                        printf("Syntax: setxy <x> <y>\n");
                    }
                }

                else if (!strcmp(cargv[0], "setcolor"))
                {
                    if (cargc > 1)
                    {
                        if (!strcmp(cargv[1], "red"))
                        {
                            setTextColor(CLEAR_RED, 0);
                            renderWindow(WN_STDWINDOW);
                            flushScreen();
                            flush();
                        }
                        else if (!strcmp(cargv[1], "green"))
                        {
                            setTextColor(GREEN, 0);
                            renderWindow(WN_STDWINDOW);
                            flushScreen();
                            flush();
                        }
                        else if (!strcmp(cargv[1], "blue"))
                        {
                            setTextColor(BLUE, 0);
                            renderWindow(WN_STDWINDOW);
                            flushScreen();
                            flush();
                        }

                        else if (!strcmp(cargv[1], "white"))
                        {
                            setTextColor(WHITE, 0);
                            renderWindow(WN_STDWINDOW);
                            flushScreen();
                            flush();
                        }
                        else
                        {
                            printf("%s is not a valid color code\n", cargv[1]);
                        }
                    }
                }

                else if (!strcmp(cargv[0], "input:"))
                {
                    char *line[1024];
                    scargv = cargc;
                    for (size_t i = 1; i < scargv; i++)
                    {
                        if (!strcmp(cargv[i], ":end"))
                        {
                            break;
                        }
                        else if (!strcmp(cargv[i], "\\n"))
                        {
                            printf("\n");
                        }
                        else
                        {
                            printf("%s ", cargv[i]);
                        }
                    }
                    scanf(line, sizeof(line));
                }
                else if (!strcmp(cargv[0], "loop"))
                {
                    if (cargc > 2)
                    {
                        for (int io = 0; io > atoi(cargv[1]); io++)
                        {
                            printf(cargv[2]);
                        }
                    }
                }

                else
                {
                    printf("Syntax error: no command named '%s' exists in the current instance\n", cargv[0]);
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
    syscall_object_close(fd);
    return 0;
}