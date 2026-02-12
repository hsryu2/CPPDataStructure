#include "List.h"

int main()
{
	List<int> list;
	
	for (int i = 0; i < 10; i++)
	{
		list.Add(i + 1);
	}
	
	std::cin.get();
}