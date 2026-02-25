#pragma once

// 데이터 필드/링크 필드를 갖는 노드 클래스.
// 연결 리스트에 저장되는 항목.
template<typename T>
class Node
{
	// 연결 리스트 friend 지정.
	template<typename T>
	friend class LinkedList;

	// 노드의 생성은 LinkedList에서만 가능하도록 private으로 지정.
private:
	Node()
		: data(), next(nullptr)
	{
	}

	Node(T data)
		: data(data), next(nullptr)
	{
	}

private:
	// 데이터 필드.
	T data;

	// 링크 필드.
	Node* next = nullptr;
};

//#include "Node.inl"
