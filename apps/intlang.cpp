/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/
/**
 * intlang: Interpreter based programming language
 * 
 * NOTE: Because this is written in C++, this will use camelcase functions
*/
#include <iostream>
#include <string>

using namespace std;

int checkSemicolon(char string[])
{
    return strEndsWith(string, ";");
}
int checkColon(char string[])
{
    return strEndsWith(string, ":");
}
int isAnnotation(char string[])
{
    return strStartsWith("@", string);
}
int isComment(char string[])
{
    return strStartsWith("-", string);
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[0], "-c"))
        {
            dbg_printf("compile mode enabled");
        } else if (!strcmp(argv[0], "-e"))
        {
            dbg_printf("interpreter mode enabled");
        }
        
    }
    else
    {
        Console::WriteLine("usage: intlang -c <file> | -e <file>\n\nOptions:\n -c: Compile the file to Assembly (Writing to disk is not supported)\n -e: Execute the file\n");
    }
    return 0;
}