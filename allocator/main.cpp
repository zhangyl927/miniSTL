#include <iostream>
#include "stackAlloc.h"
#include <time.h>
#include <vector>

#define CIRLE 5
#define XH 100000

int main()
{
    clock_t start;

    start = clock();
    Stack<int, SimpleAlloc<int>> stackTest;
    
    for (int i=0; i<CIRLE; ++i)
    {
        for (int j=0; j<XH; ++j)
        {
            stackTest.push(j);
            stackTest.push(j);
            stackTest.push(j);
            stackTest.push(j);
        }
        std::cout << stackTest.size() << std::endl;

        for (int j=0; j<XH; ++j)
        {
			stackTest.pop();
			stackTest.pop();
			stackTest.pop();
			stackTest.pop();
        }
        std::cout << stackTest.size() << std::endl;
    }

    std::cout << "stackTest spend time = " << ((double)clock()-start)/CLOCKS_PER_SEC << std::endl;

    start = clock();
	std::vector<int> vecTest;
    
    for (int i=0; i<CIRLE; ++i)
    {
        for (int j=0; j<XH; ++j)
        {
            vecTest.push_back(j);
        }
       // std::cout << vecTest.size() << std::endl;

        for (int j=0; j<XH; ++j)
        {
			vecTest.pop_back();
        }
        //std::cout << stackTest.size() << std::endl;
    }

    std::cout << "vector test spend time = " << ((double)clock()-start)/CLOCKS_PER_SEC << std::endl;

    return 0;
}
