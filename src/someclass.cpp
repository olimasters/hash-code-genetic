#include <someclass.h>
#include <iostream>

Foo::Foo(int n) :
    thing(n)
{
}

void Foo::print()
{
    std::cout << thing << std::endl;
}
