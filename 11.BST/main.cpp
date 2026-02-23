#include <iostream>
#include "Container/BinarySearchTree.h"

int main()
{

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
	tree.PreorederTraverse();

	// 중위 순회.
	tree.InorederTraverse();

	// 후위 순회.
	tree.PostorederTraverse();


	std::cin.get();

}