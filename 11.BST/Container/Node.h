#pragma once


#include <iostream>

template<typename T>

class Node
{
	template<typename T>
	friend class BinarySearchTree;
public:
	Node(const T& data, const Node<T>* const parent = nullptr)
		: data(data), parent(parent)
	{
	}

private:
	// 데이터 변수
	T data = T();

	// 부모 노드
	Node<T>* parent = nullptr;

	// 왼쪽 자식 노드
	Node<T>* left = nullptr;

	// 오른쪽 자식 노드.
	Node<T>* right = nullptr;


};