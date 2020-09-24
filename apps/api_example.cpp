#include <iostream>
#include <string>
#include <fstream>
#include <truegl/lib/button.hpp>

using namespace std;
using namespace TGL;

int main(int argc, const char *argv[])
{
    Console::WriteLine("Cadex OS C++ API examples");
    TButton *button = new TButton("Hello");
    return 0;
}