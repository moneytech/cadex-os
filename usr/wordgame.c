#include <stdio.h>
#include <library/scanf.h>

int main(int argc, char const *argv[])
{
    int i,j,k;
    char *input[1024];
    printf("Word Game v1\n");
    printf("Type HELP for help or START to start the game\n> ");
    scanf(input, sizeof(input));
    if(!strcmp(input, "HELP")){
        printf("Help code goes here\n");
    } else if (!strcmp(input, "START"))
    {
        printf("GAME STARTED\n");
    }
    return 0;
}
