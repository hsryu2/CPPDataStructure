#include "LinkedList/LinkedList.h"
#include <iostream>
//#include <list>
#include <forward_list>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(164);

	//std::forward_list<int> stlList;
	//stlList.emplace_after(stlList.begin(), 10);
	//
	//for (auto item : stlList)
	//{
	//}

	// 연결 리스트 생성.
	LinkedList<int> list;
	list.Insert(20);
	list.Insert(30);
	list.Insert(10);

	// 출력.
	std::cout << "노드 추가 후 출력\n";
	list.Print();

	// 삭제.
	//list.Delete(30);
	//list.Delete(10);

	// 출력.
	std::cout << "노드 삭제 후 출력\n";
	list.Print();

	std::cin.get();
}