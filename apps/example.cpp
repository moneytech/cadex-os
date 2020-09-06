/**
 * Example program demonstrating how to make apps for Cadex OS in C++
*/
#include <iostream>

using namespace std;

class example
{
private:
    int a = 10;

public:
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
    example ex;
    return 0;
}