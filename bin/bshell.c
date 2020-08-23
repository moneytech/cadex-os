#include <stdio.h>
#include <library/scanf.h>
#include <auth.h>

#define MAX_INPUT_CHARS 1024


int main(int argc, const char *argv[])
{
    char *cargv[100];
    int cargc;
    int scargv;
    char *input[MAX_INPUT_CHARS];
    printf("BASIC Commander v1\n");
    printf("Type HELP for a list of commands or EXIT for exiting the commander\n");
    while (1)
    {
        printf("> ");
        scanf(input, sizeof(input));
        // Number of arguments
        cargc = 0;
        // LEXER!!!
        // This is similar to cargv.split(" ") in JavaScript
        cargv[cargc] = strtok(input, " ");
        while (cargv[cargc])
        {
            cargc++;
            cargv[cargc] = strtok(0, " ");
        } 
        if(cargc > 0){
            if (!strcmp(cargv[0], "help"))
            {
                printf("List of available BASIC commands:\n");
                printf(" * PRINT: Prints text to the screen\n");
            }
            else if (!strcmp(cargv[0], "exit"))
            {
                _process_exit(0);
                return 0;
            } else if (!strcmp(cargv[0], "print"))
            {
                scargv = cargc;
                for (size_t i = 1; i < scargv; i++)
                {
                    printf("%s ", cargv[i]);
                }
                printf("\n");
            } else if (!strcmp(cargv[0], "sysexec"))
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
                printf("SYNTAX ERROR: NO COMMAND NAMED %s\n", cargv[0]);
            }
        }
    }
    //return 0;
}