#pragma once

#include "Node.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
	}

	~BinarySearchTree()
	{
		// Todo: 트리 제거 함수 구현 후 호출.
	}

	// 삽입.
	// 규칙
	// 0. 중복된 값 허용 안함.
	// 1. 루트 노드부터 비교 시작.
	// 1-1. 루트가 null이면 루트 생성.
	// 2. 추가할 값이 작으면 왼쪽에 저장.
	// 3. 추가할 값이 크면 오른쪽에 저장.
	bool InsertNode(const T& newData)
	{
		// 중복 여부 확인.
		// 	// 중복 여부 확인.
		Node<T>* outNode = nullptr;
		if (SearchNode(newData, outNode))
		{
			//
			return false;
		}
		// Todo: 검색 함수 구현 후 호출.


		// 루트가 없으면 루트 노드 생성.
		if (!root)
		{
			root = new Node<T>(newData);
			return true;
		}

		// 2/3을 처리하기 위해 재귀 함수 호출.
		root = InsertNodeRecursive(root, nullptr, newData);
		
		return true;

	}



	// 삭제.

	// 검색.
	bool SearchNode(const T& newData, Node<T>*& outNode)
	{
		// 검색 재귀함수 구현 후 호출.
		return SearchNodeRecursive(root, newData, outNode);

	}

	// 순회.

private:
	// 재귀 함수.

	// 삽입 재귀 함수.
	Node<T>* InsertNodeRecursive(
		Node<T>* node,
		Node<T>* parent,
		const T& newData)
	{
		// node가 null이면 노드 생성 후 반환.
		if (!node)
		{
			return new Node<T>(newData, parent);
		}

		// 추가하려는 값이 비교 노드 보다 작으면
		// 왼쪽 하위 트리로 탐색 진행.
		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(
				node->left, node, newData
			);
		}

		// 추가하려는 값이 비교 노드 보다 크면
		// 오른쪽 하위 트리로 탐색 진행.
		// 미리 중복 여부를 확인 했기 때문에 큰 경우만 남게된다.
		else
		{
			node->right = InsertNodeRecursive(
				node->right, node, newData
			);
	
		}

		// 트리 구조 유지를 위해 반환.
		return node;
	}

	bool SearchNodeRecursive(
		Node<T>* node,
		const T& data,
		Node<T>*& outNode)
	{
		// 검색 실패
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 찾았는지 확인.
		if (node->data == data)
		{
			outNode = node;
			return true;
		}

		// 작은 경우 왼쪽으로.
		if (node->data > data)
		{
			return SearchNodeRecursive(
				node->left, data, outNode
			);
		}

		// 큰 경우 오른쪽으로.
		else
		{
			return SearchNodeRecursive(
				node->right, data, outNode
			);
		}

	}

	// 파괴 함수.

private:
	// 루트 노드.
	Node<T>* root = nullptr;

};
