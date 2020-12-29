#include "alloc.h"
#include <iostream>

int main()
{
    int* p = static_cast<int*>(__default_alloc<int>().allocate(5));
    int *q = p;
    for (int i=0; i<5; ++i)
    {
        *q = i+2;
        ++q;
    }
    for (int i=0; i<5; ++i)
    {
        std::cout << *(p+i) << "  ";
    }
    std::cout << std::endl;

    __default_alloc<int> obj;
    obj.deallocate(p, 5);

    std::cout << *p << std::endl;
    return 0;
}