#include "List.h"

int main()
{
	List<int> list;
	
	for (int i = 0; i < 10; i++)
	{
		list.Add(i + 1);
	}
	
	// Range-based loop.
	for (const int item : list)
	{
		std::cout << item << "\n";
	}


	//loop-Iterator.
	//std::cout << "Iterator based loop \n";
	//for (
	//	List<int>::Iterator it = list.begin();
	//	it != list.end();
	//	++it)
	//{
	//	std::cout << *it << "\n";
	//}

	std::cin.get();
}