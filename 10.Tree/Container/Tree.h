#pragma once

#include "Node.h"
#include <vector>
#include <iostream>

// 트리 클래스.
template<typename T>
class Tree
{
public:
	Tree(const T& data)
	{
		// 루트 노드 생성.
		root = new Node<T>(data);
	}

	~Tree()
	{
		// 자손 노드 모두 제거하는 함수 구현 후 호출.
		DestroyRecursive(root);
	}

public:
	// 여기에 작성되는 함수를 객체지향 이론에서 "메시지"라고 지칭.
	// 메시지 = 공개(public) 메소드 - 인터페이스.
	// 객체 지향 -> 객체들이 메시지를 통해 소통하는 구조.
	// 
	// 부모 노드의 값을 사용해 해당 부모에 자손을 추가.
	bool AddChild(const T& parentData, const T& childData)
	{
		// 부모 노드 검색.
		// 검색 함수 구현 후 호출.
		Node<T>* outParent = nullptr;
		bool result = FindRecursive(parentData, root, outParent);

		// 부모 검색에 성공했으면 자손 노드 추가.
		if (result)
		{
			outParent->AddChild(childData);
			return true;
		}

		// 부모 검색에 실패하면 자손 추가 실패.
		return false;
	}

	// 검색 함수.
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	// 삭제 함수.
	bool Remove(const T& data)
	{
		// 재귀 함수 구현 후 호출.
		return RemoveRecursive(data, root);
	}

	// 전위 순회(Preorder - Traversal).
	// depth: 계층을 시각적으로 구분하기 위해 사용.
	void PreorderTraversal(int depth = 0)
	{
		// 순회 재귀 함수 구현 후 호출.
		PreorderTraversalRecursive(root, depth);
	}

private:
	// data: 검색하려는 값.
	// node: 현재 검색하는 노드.
	// outNode: 검색에 성공했을 때 반환할 노드.
	// 함수의 반환 값: 검색 성공 실패 여부.
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// 검색 실패(탈출 조건).
		if (!node)
		{
			// null 값 설정 및 함수 종료 (검색 실패).
			outNode = nullptr;
			return false;
		}

		// 노드가 가진 값이 검색하는 값인지 비교.
		// 검색 성공.
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 자손 노드로 내려가면서 재귀적으로 추가 검색 진행.
		std::vector<Node<T>*>& children = node->GetChildren();
		const int length = static_cast<int>(children.size());
		for (int ix = 0; ix < length; ++ix)
		{
			// 자손 노드 검색 진행.
			bool result = FindRecursive(data, children[ix], outNode);
			if (result)
			{
				return true;
			}
		}

		// 검색 실패.
		outNode = nullptr;
		return false;
	}


	// 삭제 재귀 함수.
	// data: 삭제할 노드의 값.
	// node: 현재 검색할 노드. RemoveImpl.
	bool RemoveRecursive(const T& data, Node<T>* node)
	{
		// 삭제할 노드 검색.
		Node<T>* outNode = nullptr;
		bool result = FindRecursive(data, node, outNode);

		// 검색에 성공했으면 삭제 진행.
		if (result)
		{
			// 부모 노드의 자손 목록에서 현재 노드 제거.
			Node<T>* parent = outNode->GetParent();
			if (parent)
			{
				// 삭제할 노드를 부모 노드 목록에서 검색.
				auto it = std::find(
					parent->GetChildren().begin(),
					parent->GetChildren().end(),
					outNode
				);

				// 목록에서 노드 제거.
				parent->GetChildren().erase(it);
			}

			// 노드가 자손이 있다면 자손 노드 제거.
			std::vector<Node<T>*>& children = outNode->GetChildren();
			while (children.size() > 0)
			{
				outNode->RemoveChild(children[0]);
			}

			// 노드 제거 및 정리.
			SafeDelete(outNode);
			//outNode = nullptr;

			return true;
		}

		// 검색 못했으면 삭제 실패.
		return false;
	}

	// 전위순회 재귀 함수.
	void PreorderTraversalRecursive(Node<T>* node, int depth = 0)
	{
		// 탈출 조건.
		if (!node)
		{
			return;
		}

		// 계층을 보여주기 위한 깊이 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 전위 순회는 부모 노드를 먼저 처리(방문).
		std::cout << node->GetData() << "\n";

		// 자손 노드 처리(방문).
		std::vector<Node<T>*>& children = node->GetChildren();
		const int length = static_cast<int>(children.size());
		if (length == 0)
		{
			return;
		}

		for (int ix = 0; ix < length; ++ix)
		{
			Node<T>* child = children[ix];
			PreorderTraversalRecursive(child, depth + 1);
		}
	}

	// 모든 노드를 제거하는 함수 (트리 파괴).
	void DestroyRecursive(Node<T>*& node)
	{
		// 자손 목록 먼저 제거.
		std::vector<Node<T>*>& children = node->GetChildren();
		while (children.size() > 0)
		{
			DestroyRecursive(children[0]);
		}

		// 부모 목록 정리.
		Node<T>* parent = node->GetParent();
		if (parent)
		{
			auto it = std::find(
				parent->GetChildren().begin(),
				parent->GetChildren().end(),
				node
			);

			if (it != parent->GetChildren().end())
			{
				parent->GetChildren().erase(it);
			}
		}

		// 노드 제거.
		SafeDelete(node);
	}

private:
	// 루트 노드.
	Node<T>* root = nullptr;
};