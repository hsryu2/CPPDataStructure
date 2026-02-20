#include "Container/Tree.h"

int main()
{
	//Node<int>* parent = new Node<int>(10);
	//Node<int>* child = new Node<int>(5);
	//parent->AddChild(child);
	//child->SetParent(parent);
	//
	//parent->RemoveChild(child);
	//
	//int number = 10;

	Tree<int> tree(10); // 10이라는 데이터를 넣은 루트 트리
	tree.AddChild(10, 9); // 10이라는 데이터를 가지고있는 트리의 9라는 데이터를 가지고있는 자손을 추가.
	tree.AddChild(10, 8);
	tree.AddChild(9, 7);
	tree.AddChild(9, 6);


	// 검색 테스트.
	Node<int>* outNode = nullptr;
	if (tree.Find(6, outNode))
	{
		int number2 = 30;
	}

	int number = 10;


}