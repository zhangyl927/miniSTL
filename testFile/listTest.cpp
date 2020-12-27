#include <iostream>
#include <ctime>

#include "../container/list/list.h"

#define CICLE 3
#define FOOLOOP 100000

int main()
{
    clock_t start;
    start = clock();
    list<int, SimpleAlloc<int>> listTest;

    for (int i=0; i<CICLE; ++i)
    {
        for (int j=0; j<FOOLOOP; ++j)
        {
            listTest.push_front(j);
            listTest.push_back(j+3);
        }

        std::cout << "list front: " << listTest.front() << ", list end: " << listTest.back() << std::endl;
        for (int j=0; j<FOOLOOP; ++j)
        {
            listTest.pop_front();
            listTest.pop_back();
        }
        std::cout << "listTest is empty? " << listTest.empty() << std::endl;
    }

    std::cout << "list spend time is: " << ((double)clock()-start)/CLOCKS_PER_SEC << std::endl;
}