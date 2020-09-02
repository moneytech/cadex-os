#include <iostream>

using namespace std;

#define MAX_CHARS 1024
#define B86_DEBUG 0

int main(int argc, char *argv[])
{
    if (argc > 0 || sizeof(argv) > 0)
    {
        cout << "usage: c2b86 [-d] -h=<input_arch> input.c output.b86\n\nOptions:\n  -d: Enable debug mode\n  -h: The type and architecture the C program is written in\n";
    } else {
    	cout << "e";
    }
}
