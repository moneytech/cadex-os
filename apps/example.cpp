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
    printf("This is a small C++ program!\n");
    example *ex;
    ex->a_string = "hello";
    printf("%s", ex->a_string);
    return 0;
}