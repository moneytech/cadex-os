#include <stdio.h>
#include <library/scanf.h>

#define MAX_INPUT_CHARS 1024
int main(int argc, const char *argv[])
{
    char *input[MAX_INPUT_CHARS];
    printf("BASIC Commander v1\n");
    printf("Type HELP for a list of commands or EXIT for exiting the commander\n");
    while(1){
        printf("> ");
        scanf(input, sizeof(input));
        if(!strcmp(input, "HELP") || !strcmp(input, "help")){
            printf("List of available BASIC commands:\n");
            printf(" * PRINT: Prints text to the screen\n");
        } else if (!strcmp(input, "EXIT" || !strcmp(input, "exit")))
        {
            return 0;
        } else
        {
            printf("SYNTAX ERROR: NO COMMAND NAMED %s", input);
        }
    }
    return 0;
}