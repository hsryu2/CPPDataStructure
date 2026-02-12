#pragma once
#include <iostream>
#include <cassert>
// 자동으로 크기가 늘어나는 배열 (List/Vector).
template<typename T>
class List
{
public:
	List()
	{
		// Todo: 저장 공간 할당 해야함.
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
		//Reallocate(capacity);
	}
	~List()
	{
		// 자원 해제.
		if (data)
		{
			delete[] data;
		}
	}
	// 값 추가 함수.
	void Add(const T& value)
	{
		// 크기가 부족한지 확인.
		if (size == capacity)
		{
			// 크기 재할당. (2배 크기로 재할당)
			Reallocate(capacity * 2);
		}

		// 항목 추가.
		data[size] = value;

		// 저장된 항목 수 증가 처리.
		++size;

	}

	void Add(T&& value)
	{
		// 크기가 부족한지 확인.
		if (size == capacity)
		{
			// 크기 재할당. (2배 크기로 재할당)
			Reallocate(capacity * 2);
		}

		// 값을 저장할 때 이동 처리.
		data[size] = std::move(value);

		// 저장된 항목 수 증가 처리.
		++size;
	}

	// 인덱스 연산자 오버로딩.
	T& operator[](int index)
	{
		// index 범위 확인.
		assert(index < 0 || index >= size);
		return data[index];
	}

	// Getter.
	int Size() const { return size; }
	int Capacity() const { return capacity; }

private:
	// 저장 공간 할당(재할당)하는 함수.
	void Reallocate(int newCapacity)
	{
		// 1. 이주할 새로운 공간 할당 (new).
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);
		
		if (newCapacity < size)
		{
			capacity = newCapacity;
		}

		// 2. 기존 항목을 새로운 공간에 복사/이동.
		//for (int i = 0; i < size; i++)
		//{
		//	newBlock[i] = data[i];
		//}
		// 메모리 복사. 위와같은 방법으로 해도 되긴함.
		memcpy(newBlock, data, sizeof(T) * capacity);

		
		// 3. 기존 배열 공간 해제.
		delete[] data;
		data = newBlock; // 영역 나가면 메모리에서 빠질 예정.
		capacity = newCapacity;
	}

	

private:
	// 힙에 할당되는 배열을 관리할 포인터 변수.
	T* data = nullptr;

	// 배열에 저장된 항목의 수
	int size = 0;

	// 배열 저장 공간의 크기.
	int capacity = 2;


};