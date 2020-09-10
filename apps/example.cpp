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
    example(/* args */);
    ~example();
};

example::example(/* args */)
{
    printf("Constructor\n");
    printf("%d\n", example::a);
}

example::~example()
{
    printf("Destructor\n");
}

int main(int argc, const char *argv[])
{
    printf("This is a small C++ program! If you see this message, that means you can make apps for Cadex OS with C++!\n");
    example *ex;
    string *mystring = new string("Hello");
    Console::Write(mystring->getValue());
    printf("%s", mystring->getValue());
    return 0;
}