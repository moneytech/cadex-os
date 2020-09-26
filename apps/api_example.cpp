#include <iostream>
#include <string>
#include <fstream>
#include <truegl/lib/button.hpp>
#include <sys/logger.h>

using namespace std;
using namespace TGL; 
 
int main(int argc, const char *argv[])
{
    Console::WriteLine("Cadex OS C++ API examples");
    printf("hello\rhelloworld\n");
    LOG("This is a log\n", 0);
    ELOG("This is an error; Error number is %d\n", KERROR_NOT_FOUND);
    return 0;
}