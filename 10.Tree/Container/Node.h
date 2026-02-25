#pragma once

#include <vector>

// 노드 삭제 편의 함수.
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

// 트리의 구성요소가 될 노드 클래스.
template<typename T>
class Node
{
public:
	Node()
		: data()
	{
	}

	Node(const T& data)
		: data(data)
	{
	}

	~Node()
	{
		// 리소스 정리.
		data = T();
		parent = nullptr;
		children.clear();
	}

public:
	// 값을 전달해 자손 추가하는 함수.
	// 래퍼(Wrapper) 함수 -> 다른 함수를 외부에서 감싸는 형태.
	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}

	// 노드를 직접 전달해 자손 추가하는 함수.
	void AddChild(Node<T>* newChild)
	{
		// 현재 노드를 부모 노드로 지정.
		newChild->SetParent(this);

		// 자손 노드 목록에 새 노드 추가.
		children.emplace_back(newChild);
	}

	// 노드 삭제.
	void RemoveChild(Node<T>* child)
	{
		// 하위노드까지 순회하면서 노드 검색 후 삭제.
		// 재귀 함수.
		RemoveChildRecursive(child);
	}

	// Getter/Setter.
	inline T GetData() const { return data; }
	inline std::vector<Node<T>*>& GetChildren() { return children; }
	inline Node<T>* GetParent() const { return parent; }
	inline void SetParent(Node<T>* newParent) { parent = newParent; }

private:
	// 노드 삭제 재귀 함수.
	// 파스칼 케이싱/캐멀 케이싱/스네이크 케이싱.
	// 재귀 함수 -> 자기 자신을 호출하는 함수.
	// 언제 사용하는가? -> 자기 자신을 호출하면서 데이터의 범위가 줄어들 때.
	// 주의사항! - 탈출 조건이 항상 있어야 함.
	// 주의사항! - 스택 오버플로우 위험이 있음 (콜 스택을 사용하기 때문).
	// 로직 이해하는데는 좋지만, 루프(for등)로 로직을 변환하는게 더 좋음.
	void RemoveChildRecursive(Node<T>* child)
	{
		// 탈출 조건.
		if (!child) // if (child == nullptr)
		{
			return;
		}

		// 하위 노드 확인.
		std::vector<Node<T>*>& children = child->GetChildren();

		// 경우의 수1 - 자손이 없는 경우.
		if (children.size() == 0)
		{
			// 부모 노드의 자손 목록 가져오기.
			auto& parentVector = child->GetParent()->GetChildren();

			// 자손 목록에서 삭제할 노드 검색(반환 타입은 iterator).
			auto childIt = std::find(
				parentVector.begin(),
				parentVector.end(),
				child
			);

			// 자손 목록에서 노드 검색에 성공했으면, 해당 노드 제거.
			if (childIt != parentVector.end())
			{
				parentVector.erase(childIt);
			}

			// 노드 삭제.
			SafeDelete(child);
			return;
		}

		// 경우의 수2 - 자손 노드가 있는 경우.
		while (children.size() > 0)
		{
			// 자손을 순회하면서 재귀 삭제 함수 호출.
			RemoveChildRecursive(children[0]);
		}

		// 마무리.
		// 부모 노드의 자손 목록 가져오기.
		auto& parentVector = child->GetParent()->GetChildren();

		// 자손 목록에서 삭제할 노드 검색(반환 타입은 iterator).
		auto childIt = std::find(
			parentVector.begin(),
			parentVector.end(),
			child
		);

		// 자손 목록에서 노드 검색에 성공했으면, 해당 노드 제거.
		if (childIt != parentVector.end())
		{
			parentVector.erase(childIt);
		}

		// 노드 삭제.
		SafeDelete(child);
	}

private:
	// 노드에 저장할 데이터.
	T data;

	// 부모 참조 변수.
	Node<T>* parent = nullptr;

	// 자손 노드 리스트(동적 배열).
	std::vector<Node<T>*> children;
};