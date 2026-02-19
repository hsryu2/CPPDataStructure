#include "List.h"
#include <iostream>
#include <vector>

int main()
{
	List<int> list;
	for (int ix = 0; ix < 10; ++ix)
	{
		list.Add(ix + 1);
	}

	// Range-based loop.
	std::cout << "Range-based loop\n";
	for (const int item : list)
	{
		std::cout << item << "\n";
	}

	// loop - Iterator.
	//std::cout << "Iterator based loop\n";
	//for (
	//	List<int>::Iterator it = list.begin(); 
	//	it != list.end(); 
	//	++it)
	//{
	//	std::cout << *it << "\n";
	//}

	std::cin.get();
}