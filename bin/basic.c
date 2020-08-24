#include <stdio.h>
#include <library/scanf.h>
#include <auth.h>
#include <library/string.h>

#define MAX_INPUT_CHARS 1024

int main(int argc, const char *argv[])
{
    char *cargv[100];
    int cargc;
    int scargv;
    char *input[MAX_INPUT_CHARS];
    int basic_is;
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
        while ((n = syscall_object_read(fd, buffer, 100)) > 0)
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
                if (!strcmp(cargv[0], "help"))
                {
                    printf("List of available BASIC commands:\n");
                    printf(" * PRINT: Prints text to the screen\n");
                }
                else if (!strcmp(cargv[0], ":end"))
                {
                    continue;
                }
                else if (!strcmp(cargv[0], "exit"))
                {
                    syscall_object_close(fd);
                    _process_exit(0);
                    return 0;
                }
                else if (!strcmp(cargv[0], "print:"))
                {
                    scargv = cargc;
                    for (size_t i = 1; i < scargv; i++)
                    {
                        printf("%s ", cargv[i]);
                    }
                    printf("\n");
                }
                else if (!strcmp(cargv[0], "true"))
                {
                    printf("[builtin-keyword] true: Has a value of 1, on, or yes");
                }

                else if (!strcmp(cargv[0], "sysexec"))
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
                else if (!strStartsWith(";", cargv[0]))
                {
                    printf("");
                }
                else
                {
                    printf("SYNTAX ERROR: NO COMMAND NAMED %s\n", cargv[0]);
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