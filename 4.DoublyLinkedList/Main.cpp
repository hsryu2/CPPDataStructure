#include "LinkedList/LinkedList.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkedList<int> list;
	for (int ix = 0; ix < 10; ++ix)
	{
		list.InsertLast((ix + 1) * 10);
	}

	std::cout << "리스트 추가 후 출력\n";
	list.Print();

	// 항목 제거.
	list.Delete(20);
	list.Delete(50);
	list.Delete(80);

	std::cout << "리스트 제거 후 출력\n";
	list.Print();

	std::cin.get();
}