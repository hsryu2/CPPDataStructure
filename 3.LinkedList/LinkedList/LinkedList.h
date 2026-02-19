#pragma once

#include "Node.h"
#include <iostream>

// 메모리 레이아웃.
//class Test
//{
//	int value;
//	int* test;
//};

// 단일 연결 리스트 클래스.
// Node를 내부에서 관리.
// 정렬 기반으로 노드 추가 (전제: 비교가 가능해야 함).
template<typename T>
class LinkedList
{
	// 타입 알리아싱 지정.
	using NodeType = Node<T>*;

public:
	LinkedList()
		: head(nullptr), count(0)
	{
	}
	
	~LinkedList()
	{
		// 메모리 정리.
		NodeType current = head;
		NodeType next = nullptr;

		// 순회하면서 메모리 해제.
		while (current)
		{
			// 삭제하기 전에 다음 노드 미리 저장.
			next = current->next;

			// 삭제.
			delete current;

			// 다음 노드로 이동.
			current = next;
		}

		// 정리.
		head = nullptr;
		count = 0;
	}

	// 노드 추가 함수.
	void Insert(const T& data)
	{
		// 새노드 생성.
		NodeType newNode = new Node<T>(data);

		// 노드를 삽입할 위치 확인.

		// 헤드가 빈 상태인지 확인.
		if (!head)
		{
			// 헤드 노드를 새 노드로 지정.
			head = newNode;
		}

		// 헤드가 있으면 추가할 위치 검색 후 추가.
		else
		{
			// 자리 검색을 위한 변수.
			NodeType current = head;
			NodeType trail = nullptr;

			// 자리 검색.
			while (current)
			{
				// 값 비교.
				if (current->data >= data)
				{
					break;
				}

				// 다음 노드로 검색 이어가기.
				trail = current;
				current = current->next;
			}

			// 검색한 위치가 헤드인 경우.
			if (current == head)
			{
				// newNode를 헤드로 전환.
				newNode->next = head;
				head = newNode;
			}

			// 헤드가 아닌 경우.
			else
			{
				// 삽입할 위치에서 포인터 정리.
				newNode->next = current;
				trail->next = newNode;
			}
		}

		// 저장 개수 증가.
		++count;
	}

	// 노드 제거 함수.
	void Delete(const T& data)
	{
		// 예외 처리 (빈 리스트는 지울게 없음).
		if (!head)
		{
			std::cout << "List is empty.\n";
			return;
		}

		// 삭제할 노드 검색.
		NodeType current = head;
		NodeType trail = nullptr;

		while (current)
		{
			// 값 비교.
			if (current->data == data)
			{
				break;
			}

			// 다음 노드로 검색 이어가기.
			trail = current;
			current = current->next;
		}

		// 예외처리.
		if (!current)
		{
			// 검색 실패한 경우.
			std::cout << "Failed to find the node.\n";
			return;
		}

		// 삭제할 노드가 헤드인 경우.
		if (head == current)
		{
			// 기존 헤드의 다음 노드를 새 헤드로 설정.
			head = head->next;
		}

		// 헤드가 아닌 경우.
		else
		{
			// 포인터 정리.
			trail->next = current->next;
		}

		// 메모리 해제.
		delete current;

		// 제거 처리.
		--count;
	}

	// 출력 함수.
	void Print()
	{
		// 처음부터 순회하면서 값 출력.
		NodeType current = head;

		// 순회.
		while (current)
		{
			// 현재 노드의 값 출력.
			std::cout << "Data: " << current->data << "\n";

			// 다음 노드로 이동.
			current = current->next;
		}
	}

private:
	// 헤드(머리) 노드.
	//Node<T>* head = nullptr;
	NodeType head = nullptr;

	// 연결 리스트에 저장된 항목의 수.
	int count = 0;
};