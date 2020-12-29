#include <iostream>
#include <ctime>

#include "../container/list/list.h"

int main()
{
    list<int, SimpleAlloc<int>> list1;

	std::cout << "list1 push: ";
    for (int i=0; i<5; ++i)
    {
   		list1.push_front(i);
    	list1.push_back(i+3);
	}

	for (auto i:list1)
	{
		std::cout << i << ",  ";
	}    
	
	std::cout << "\nlist1 front: " << list1.front() << ", list1 end: " << list1.back() << std::endl;
    
	std::cout << "list2(list1) copy construct: ";
	list<int, SimpleAlloc<int>> list2(list1);
	for (auto i:list2)
	{
		std::cout << i << ",  ";
	}

	std::cout << "\nlist2 reverse: ";
	for (auto i=list2.rbegin(); i!=list2.rend(); ++i)
	{
		std::cout << *i << ",  ";
	}

	std::cout << "\nlist2.size() = " << list2.size() << std::endl;

	for (int i=0; i<5; ++i)
	{
		list1.pop_front();
        list1.pop_back();
    }
   

	std::cout << "list1 after pop: ";
	for (auto i:list1)
	{
		std::cout << i << ",  ";
	}

	std::cout << "\nlist2=list1 before operator=: ";
	for (auto i:list2)
	{
		std::cout << i << ",  ";
	}

	list2 = list1;
	std::cout << "\nafter operator=: ";
	for (auto i:list2)
	{
		std::cout << i << ",  ";
	}

	std::cout << "\nlist1 is empty? " << list1.empty() << std::endl;

	return 0;
}
