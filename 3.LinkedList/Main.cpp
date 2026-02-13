#include <iostream>
#include "LinkedList/LinkedList.h"

int main()
{
	
	LinkedList<int> list;
	list.Insert(20);
	list.Insert(30);
	list.Insert(10);

	// Ãâ·Â.
	list.Print();

	list.Delete(30);
	list.Delete(10);

	list.Print();

	std::cin.get();

}