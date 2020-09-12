/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * Example program demonstrating how to make apps for Cadex OS in C++
*/
#include <iostream>
#include <string>

using namespace std;

class example
{
private:
    int a = 10;

public:
    char *a_string;
    example();
    auto example_function() -> void;
    ~example();
};

// TEST: Constructor
example::example()
{
    printf("\nConstructor\n");
    printf("%d\n", example::a);
}

// TEST: Destructor
example::~example()
{
    printf("\nDestructor\n");
}

// TEST: Method
auto example::example_function() -> void
{
    Console::WriteLine("Calling from a function!");
}

int main(int argc, const char *argv[])
{
    Console::Write("C++ Test");

    // TEST: Class init
    example ex = example();

    // TEST: String creation
    String *mystring = new String("Hello\n");

    // TEST: Output the value of mystring to the console
    Console::Write(mystring->getValue());

    // TEST: Function call from example class
    ex.example_function();
    return 0;
}