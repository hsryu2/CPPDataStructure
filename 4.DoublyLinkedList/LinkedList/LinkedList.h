#pragma once

#include "Node.h"
#include <iostream>

template<typename T>
class LinkedList
{
public:

	// 생성자.
	LinkedList()
		: first(new Node<T>()),
		last(new Node<T>()),
		count(0)
	{
		// 처음과 마지막 노드 연결.
		first->next = last;
		last->previous = first;
	}

	~LinkedList()
	{
		//// 힙 메모리 오류 확인 함수.
		//if (_heapchk() != _HEAPOK)
		//{
		//	__debugbreak();
		//}

		// 메모리 정리.
		Clear();

		//// 힙 메모리 오류 확인 함수.
		//if (_heapchk() != _HEAPOK)
		//{
		//	__debugbreak();
		//}

		delete first;
		first = nullptr;

		//// 힙 메모리 오류 확인 함수.
		//if (_heapchk() != _HEAPOK)
		//{
		//	__debugbreak();
		//}

		delete last;
		last = nullptr;

		//// 힙 메모리 오류 확인 함수.
		//if (_heapchk() != _HEAPOK)
		//{
		//	__debugbreak();
		//}
	}

	// 정리 함수.
	void Clear()
	{
		// 데이터를 갖는 첫 항목부터 삭제.
		Node<T>* current = first->next;

		// 마지막 노드 도달 전까지 반복.
		while (current && current != last)
		{
			// 다음 노드 임시 저장.
			Node<T>* next = current->next;

			// 현재 노드 삭제.
			delete current;

			// 다음 노드로 이동.
			current = next;
		}

		// 값 정리.
		count = 0;

		// 초기 상태로 리셋.
		first->next = last;
		last->previous = first;
	}

	// 검색 함수.
	Node<T>* Find(const T& data)
	{
		// 첫 노드부터 검색 시작.
		Node<T>* current = first->next;

		while (current && current != last)
		{
			// 값 비교.
			if (current->data == data)
			{
				return current;
			}

			// 다음 노드로 이동.
			current = current->next;
		}

		std::cout << "Can't find the data.\n";
		return nullptr;
	}

	// 역방향 검색 함수.
	Node<T>* FindReverse(const T& data)
	{
		// 마지막 노드부터 검색 시작.
		Node<T>* current = last->previous;

		while (current && current != first)
		{
			// 값 비교.
			if (current->data == data)
			{
				return current;
			}

			// 이전 노드로 이동.
			current = current->previous;
		}

		std::cout << "Can't find the data.\n";
		return nullptr;
	}

	// 첫 위치에 추가하는 함수.
	void InsertFirst(const T& data)
	{
		// 새 노드 생성.
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		// 포인터 정리.
		// 새 노드의 다음 노드를 first->next(기존의 첫 노드).
		// 이전 first->next의 이전 노드(previous)를 새 노드로 설정.
		Node<T>* next = first->next;
		newNode->next = next;
		next->previous = newNode;

		// first->next 노드를 새 노드로,
		// 새 노드의 이전 노드를 first로 설정.
		first->next = newNode;
		newNode->previous = first;

		// 노드 증가 처리.
		++count;
	}

	// 마지막 위치에 항목 추가하는 함수.
	void InsertLast(const T& data)
	{
		// 새 노드 생성.
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		Node<T>* previous = last->previous;
		previous->next = newNode;
		newNode->previous = previous;

		newNode->next = last;
		last->previous = newNode;

		// 증가 처리.
		++count;
	}

	// 삭제 함수.
	void Delete(const T& data)
	{
		// 리스트가 비었는지 확인.
		if (count == 0)
		{
			std::cout << "List is emtpy.\n";
			return;
		}

		// 삭제할 노드 검색 (순방향 검색).
		Node<T>* deleteNode = Find(data);

		// 검색 실패 확인.
		if (!deleteNode)
		{
			std::cout << "Failed to find data to delete.\n";
			return;
		}

		// 포인터 정리.
		deleteNode->previous->next = deleteNode->next;
		deleteNode->next->previous = deleteNode->previous;

		// 노드 제거.
		delete deleteNode;
		deleteNode = nullptr;

		// 항목 감소.
		--count;
	}

	// 출력 함수.
	void Print()
	{
		// 첫 항목부터.
		Node<T>* current = first->next;

		std::cout << "List item count: " << count << "\n";

		while (current != last)
		{
			// 노드의 데이터 출력.
			std::cout << "Item: " << current->data << "\n";

			// 다음 노드로 이동.
			current = current->next;
		}
	}

private:
	// 첫 번째 노드.
	Node<T>* first = nullptr;

	// 마지막 노드.
	Node<T>* last = nullptr;

	// 저장된 항목 수.
	int count = 0;
};