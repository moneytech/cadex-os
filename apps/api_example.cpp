#include <fstream>
#include <iostream>
#include <string>
#include <sys/logger.h>
#include <truegl/truegl.h>
#include <truegl/glx.hpp>

using namespace std;
using namespace TGL;

int main(int argc, const char *argv[]) {
    // You can use Console::WriteLine to write plain string to the console
    Console::WriteLine("Console::WriteLine(\"Hello World!\");");

    // You can use the traditional printf() function to print formatted text to
    // the screen
    printf("printf(\"Hello World!\");\n");

    // You can use dbg_printf() to print formatted debug messages to the
    // serial port COM1
    dbg_printf("dbg_printf(\"Hello World!\")");

    // You can use setup_window() function to set up the console for graphical
    // actions like drawing rectangle, drawing lines .etc
    setup_window();

	// To draw a rectangle, you can use the drawRect() function.
    drawRect(10,10,100,100);
    return 0;
}
