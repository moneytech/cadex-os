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

example::example()
{
    printf("Constructor\n");
    printf("%d\n", example::a);
}

example::~example()
{
    printf("Destructor\n");
}

auto example::example_function() -> void
{
    Console::WriteLine("Calling from a function!");
}

int main(int argc, const char *argv[])
{
    Console::Write("This is a small C++ program! If you see this message, that means you can make apps for Cadex OS with C++!");
    example ex = example();
    String *mystring = new String("Hello\n");
    Console::Write(mystring->getValue());
    ex.example_function();
    return 0;
}