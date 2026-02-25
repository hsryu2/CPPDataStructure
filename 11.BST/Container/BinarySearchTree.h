#pragma once

#include "Node.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

// 이진 탐색 트리 클래스.
template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
	}

	~BinarySearchTree()
	{
		// 트리 제거 함수 호출.
		Destroy();
	}

	// 삽입.
	// 규칙.
	// 0. 중복된 값 허용 안함.
	// 1. 루트 노드부터 비교 시작.
	// 1-1. 루트가 null이면 루트 생성.
	// 2. 추가할 값이 작으면 왼쪽에 저장.
	// 3. 추가할 값이 크면 오른쪽에 저장.
	bool InsertNode(const T& newData)
	{
		// 중복 여부 확인.
		Node<T>* outNode = nullptr;
		if (SearchNode(newData, outNode))
		{
			// 중복된 값이 있으면 삽입 실패.
			return false;
		}

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
	bool DeleteNode(const T& deleteData)
	{
		// 재귀 삭제 함수 구현 후 호출.
		return DeleteNodeRecursive(root, deleteData, root);
	}

	// 검색.
	bool SearchNode(const T& data, Node<T>*& outNode)
	{
		// 검색 재귀함수 구현 후 호출.
		return SearchNodeRecursive(root, data, outNode);
	}

	// 순회.
	// 전위 순회.
	void PreorderTraverse(int depth = 0)
	{
		std::cout << "========= 전위 순회 시작 =========\n";

		// 순회 재귀 함수 호출.
		PreorderTraverseRecursive(root, depth);

		std::cout << "========= 전위 순회 종료 =========\n";
	}

	void InorderTraverse(int depth = 0)
	{
		std::cout << "========= 중위 순회 시작 =========\n";

		// 순회 재귀 함수 호출.
		InorderTraverseRecursive(root, depth);

		std::cout << "========= 중위 순회 종료 =========\n";
	}

	void PostorderTraverse(int depth = 0)
	{
		std::cout << "========= 후위 순회 시작 =========\n";

		// 순회 재귀 함수 호출.
		PostorderTraverseRecursive(root, depth);

		std::cout << "========= 후위 순회 종료 =========\n";
	}

private:
	// 재귀 함수.

	// 전위 순회 재귀 함수.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		// 뎁스 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리. node == node->parent->left ? "L: "..
		std::cout << node->data << "\n";

		// 왼쪽 하위 트리 처리.
		PreorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 하위 트리 처리.
		PreorderTraverseRecursive(node->right, depth + 1);
	}

	void InorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		// 왼쪽 하위 트리 처리.
		InorderTraverseRecursive(node->left, depth + 1);

		// 뎁스 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리. node == node->parent->left ? "L: "..
		std::cout << node->data << "\n";

		// 오른쪽 하위 트리 처리.
		InorderTraverseRecursive(node->right, depth + 1);
	}

	void PostorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		// 왼쪽 하위 트리 처리.
		PostorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 하위 트리 처리.
		PostorderTraverseRecursive(node->right, depth + 1);

		// 뎁스 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리. node == node->parent->left ? "L: "..
		std::cout << node->data << "\n";
	}


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
		else
		{
			node->right = InsertNodeRecursive(
				node->right, node, newData
			);
		}

		// 트리 구조 유지를 위해 반환.
		return node;
	}

	// 검색 재귀 함수.
	bool SearchNodeRecursive(
		Node<T>* node,
		const T& data,
		Node<T>*& outNode)
	{
		// 검색 실패.
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

	// 삭제 재귀 함수.
	bool DeleteNodeRecursive(
		Node<T>* node,
		const T& deleteData,
		Node<T>*& outNode)
	{
		// 노드가 null인 경우는 삭제할 노드를 찾지 못한 경우.
		// 삭제 실패.
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 비교 값이 작은 경우 왼쪽으로.
		if (node->data > deleteData)
		{
			return DeleteNodeRecursive(
				node->left, deleteData, node->left
			);
		}

		// 비교 값이 큰 경우 오른쪽으로.
		else if (node->data < deleteData)
		{
			return DeleteNodeRecursive(
				node->right, deleteData, node->right
			);
		}

		// 삭제 노드 찾은 경우 처리.
		else
		{
			// 경우의 수1 - 자식이 없는 경우.
			// (left,right 모두 null)
			if (!node->left && !node->right)
			{
				delete node;
				outNode = nullptr;
				return true;
			}

			// 경우의 수2 - 자식 노드 둘 다 있는 경우.
			if (node->left && node->right)
			{
				// 여기에서는 2가지 방법이 가능.
				// 1. 왼쪽 하위 트리에서 가장 큰 값의 노드를 대체.
				// 2. 오른쪽 하위 트리에서 가장 작은 값의 노드를 대체.
				// 하위 노드에서 최소값 찾는 함수 호출.
				node->data = SearchMinValue(node->right)->data;

				// 오른쪽 하위 트리에서 가장 작은 값의 노드를 삭제
				// 및 정리.
				DeleteNodeRecursive(
					node->right, node->data, node->right
				);

				return true;
			}

			// 경우의 수3 - 둘 중에 하나만 있는 경우.
			else
			{
				// 왼쪽 자손이 null -> 오른쪽 자손만 있는 경우.
				if (!node->left)
				{
					// 오른쪽 자손 정보를 임시 저장.
					Node<T>* right = node->right;

					// 오른쪽 자손의 부모를 삭제할 노드의 부모로 설정.
					right->parent = node->parent;

					// 노드 제거.
					delete node;

					// 오른쪽 자손 정보 설정.
					outNode = right;
					return true;
				}
				// 왼쪽 자손이 있는 경우.
				else if (!node->right)
				{
					// 왼쪽 자손 정보를 임시 저장.
					Node<T>* left = node->left;

					// 왼쪽 자손의 부모를 삭제할 노드의 부모로 설정.
					left->parent = node->parent;

					// 노드 제거.
					delete node;

					// 왼쪽 자손 정보 설정.
					outNode = left;
					return true;
				}
			}
		}

		// 오류.
		outNode = nullptr;
		return false;
	}

	// 최소값 검색 함수.
	// node: 검색을 시작하는 노드.
	Node<T>* SearchMinValue(Node<T>* node)
	{
		// 검색 시작.
		while (node->left)
		{
			// 왼쪽 하위 노드로 이동.
			node = node->left;
		}

		// 최소 값을 가진 노드 반환.
		return node;
	}

	// 파괴 함수.
	void Destroy()
	{
		// 빈 트리(root가 null)인 경우에는 함수 종료.
		if (!root)
		{
			return;
		}

		// 루트 노드부터 제거.
		DestroyRecursive(root);
	}

	// 파괴 재귀 함수.
	void DestroyRecursive(Node<T>* node)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		// 자손이 없는 경우 처리.
		if (!node->left && !node->right)
		{
			delete node;
			return;
		}

		// 왼쪽 하위 트리 삭제.
		DestroyRecursive(node->left);

		// 오른쪽 하위 트리 삭제.
		DestroyRecursive(node->right);

		// 노드 정리.
		delete node;
	}

private:
	// 루트 노드.
	Node<T>* root = nullptr;
};