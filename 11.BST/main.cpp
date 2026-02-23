#include <iostream>
#include "Container/BinarySearchTree.h"

int main()
{
	// 정수형 이진 탐색 트리 객체 생성.
	BinarySearchTree<int> tree;

	// 삽입.
	tree.InsertNode(10);
	tree.InsertNode(20);
	tree.InsertNode(5);
	tree.InsertNode(30);

	std::cin.get();

}