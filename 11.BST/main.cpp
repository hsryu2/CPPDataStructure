#include "Container/BinarySearchTree.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 정수형 이진 탐색 트리 객체 생성.
	BinarySearchTree<int> tree;

	// 삽입.
	tree.InsertNode(20);
	tree.InsertNode(10);
	tree.InsertNode(5);
	tree.InsertNode(30);
	tree.InsertNode(25);
	tree.InsertNode(35);
	tree.InsertNode(8);

	// 삭제.
	tree.DeleteNode(30);
	tree.DeleteNode(10);
	tree.DeleteNode(8);

	// 전위 순회.
	tree.PreorderTraverse();

	// 중위 순회.
	tree.InorderTraverse();

	// 후위 순회.
	tree.PostorderTraverse();

	std::cin.get();
}