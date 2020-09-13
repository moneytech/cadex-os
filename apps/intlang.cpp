/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/
/**
 * intlang: Interpreter based programming language
*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    if(argc > 1){

    } else {
        Console::WriteLine("usage: intlang -c <file> | -e <file>\n\nOptions:\n -c: Compile the file to Assembly (Writing to disk is not supported)\n -e: Execute the file\n");
    }
    return 0;
}