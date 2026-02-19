#pragma once

template<typename T>
class Node
{
	// LinkedList 클래스 friend로 등록.
	template<typename T>
	friend class LinkedList;

public:
	// 생성자.
	Node()
		: data(), next(nullptr), previous(nullptr)
	{
	}


private:
	// 데이터 필드.
	T data;

	// 다음 노드 가리키는 링크 필드.
	Node<T>* next = nullptr;
	
	// 이전노드 가리키는 링크 필드.
	Node<T>* previous = nullptr;
};