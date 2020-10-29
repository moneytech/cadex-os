/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/ 

#include <fstream>
#include <iostream>
#include <library/scanf.h>
#include <string>
#include <truegl/truegl.h>

using namespace std;
using namespace TGL;

// Used for scanf() demo
char input[1024];

int main(int argc, const char* argv[])
{
    // You can use Console::WriteLine to write plain string to the console
    Console::WriteLine("Console::WriteLine(\"Hello World!\");");

    // You can use the traditional printf() function to print formatted text to
    // the screen
    printf("printf(\"Hello World!\");\n");

    // Scanf in CadexOS is a bit different. It doesn't
    // allow you to take formatted input from the
    // keyboard regardless of its function name
    scanf(input, sizeof(input));

    // You can parse command-line arguments just like you do on other
    // operating systems
    printf("command-line arguments: argc=%d, argv='%s'", argc, (char*)argv);

    // You can use dbg_printf() to print formatted debug messages to the
    // serial port COM1
    dbg_printf("dbg_printf(\"Hello World!\")");

    // You can use setup_window() function to set up the console for graphical
    // actions like drawing rectangle, drawing lines .etc
    setup_window();

    // To draw a rectangle, you can use the drawRect() function.
    drawRect(10, 10, 100, 100);
    return 0;
}
