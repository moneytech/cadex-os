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
#include <memory>
#include <sul/urlparser.h>

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
    printf("\nConstructor: example::example()\n");
    printf("%d\n", example::a);
}

// TEST: Destructor
example::~example()
{
    printf("\nDestructor: example::~example()\n");
}

// TEST: Method
auto example::example_function() -> void
{
    Console::WriteLine("Function call: example::example_function()");
}


int main(int argc, const char *argv[])
{

    Console::Write("-- C++ Test");

    // TEST: Class init
    example *ex = new example();

    // TEST: Function call from example class
    ex->example_function();

    // TEST: Deletion of example class
    delete ex;

    // TEST: String creation
    String *mystring = new String("Test: String:  This is a string\n");

    // TEST: Output the value of mystring to the console
    Console::Write(mystring);

    Console::WriteLine("-- C++ tests completed.");
    Console::WriteLine("-- LibC Test");
    Console::WriteLine("?? Yuarel URL Parsing Library tests ??");

    int p;
    struct yuarel url;
    struct yuarel_param params[3];
    char *parts[3];
    char url_string[] = "http://localhost:8989/path/to/test?query=yes#frag=1";
    printf("Test URL: %s\n", url_string);
    if (-1 == yuarel_parse(&url, url_string))
    {
        printf("!! Tests failed: Could not parse url!\n");
        return 1;
    }

    printf("URL scheme:  %s\n", url.scheme);
    printf("URL host:  %s\n", url.host);
    printf("URL port:  %d\n", url.port);
    printf("URL path:  %s\n", url.path);
    printf("URL query:  %s\n", url.query);
    printf("URL fragment:  %s\n", url.fragment);

    if (3 != yuarel_split_path(url.path, parts, 3))
    {
        printf("!! Tests failed: Could not split path!\n");
        return 1;
    }

    printf("URL path parts: %s, %s, %s\n", parts[0], parts[1], parts[2]);

    printf("Query string parameters:\n");

    p = yuarel_parse_query(url.query, '&', params, 3);
    while (p-- > 0)
    {
        printf("Param %s = %s\n", params[p].key, params[p].val);
    }
    Console::WriteLine("-- Yuarel tests completed. ");
    Console::WriteLine("-- All tests completed. ");
    return 0;
}