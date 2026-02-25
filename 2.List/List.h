#pragma once

#include <iostream>
#include <cassert>

// 반복자.
template<typename List>
class ListIterator
{
public:
	// 타입 알리아싱 지정.
	// List가 템플릿 파라미터로 넘어오는 경우 typename 까지 지정.
	using ValueType = typename List::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ListIterator(PointerType ptr)
		: ptr(ptr)
	{
	}

	// 연산자 오버로딩.

	// 전위 증가 연산자.
	ListIterator& operator++()
	{
		++ptr;
		return *this;
	}

	// 후위 증가 연산자.
	ListIterator& operator++(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		// 내부 포인터 ++ 처리.
		++(*this);

		// 앞서 저장했던 반복자 반환.
		return iterator;
	}

	// 전위 감소 연산자.
	ListIterator& operator--()
	{
		--ptr;
		return *this;
	}

	// 후위 감소 연산자.
	ListIterator& operator--(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		// 내부 포인터 -- 처리.
		--(*this);

		// 앞서 저장했던 반복자 반환.
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(ptr + index);
	}

	PointerType operator->()
	{
		return ptr;
	}

	ReferenceType operator*()
	{
		return *ptr;
	}

	// 비교 연산자 오버로딩.
	bool operator==(const ListIterator& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const ListIterator& other) const
	{
		return !(*this == other);
	}

private:
	// 반복자는 결국 포인터.
	PointerType ptr = nullptr;
};

// 자동으로 크기가 늘어나는 배열 (List/Vector).
template<typename T>
class List
{
	// 타입 알리아싱 지정.
public:
	using ValueType = T;
	using Iterator = ListIterator< List<T> >;

public:
	List()
	{
		// 저장 공간 할당.
		Reallocate(capacity);
		//data = new T[capacity];
		//memset(data, 0, sizeof(T) * capacity);
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
		// 크기가 부족한지 확인 (가득찬 상태인지 확인).
		if (size == capacity)
		{
			// 크기 재할당 (2배 크기로 재할당).
			Reallocate(capacity * 2);
		}

		// 항목 추가.
		data[size] = value;
		
		// 저장된 항목 수 증가 처리.
		++size;
	}

	void Add(T&& value)
	{
		// 크기가 부족한지 확인 (가득찬 상태인지 확인).
		if (size == capacity)
		{
			// 크기 재할당 (2배 크기로 재할당).
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
		//assert(index < 0 || index >= size);
		assert(index >= 0 && index < size);
		return data[index];
	}

	// Getter.
	int Size() const { return size; }
	int Capacity() const { return capacity; }

	// 범위 기반 루프 처리를 위한 함수 작성 (begin/end).
	// 배열의 첫 위치를 반환하는 함수.
	Iterator begin()
	//T* begin()
	{
		return Iterator(data);
		//return data;
	}

	// 배열에 저장된 마지막 요소의 다음 위치를 반환하는 함수.
	Iterator end()
	//T* end()
	{
		return Iterator(data + size);
		//return data + size;
	}

private:
	// 저장 공간 할당(재할당)하는 함수.
	void Reallocate(int newCapacity)
	{
		// 1. 이주할 새로운 공간 할당 (new).
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		if (newCapacity < size)
		{
			size = newCapacity;
		}

		// 2. 기존 항목을 새로운 공간에 복사/이동.
		//for (int ix = 0; ix < size; ++ix)
		//{
		//	newBlock[ix] = data[ix];
		//}
		// 메모리 복사.
		if (data)
		{
			memcpy(newBlock, data, sizeof(T) * size);
		}

		// 3. 기존 배열 공간 해제.
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	// 힙에 할당되는 배열을 관리할 포인터 변수.
	T* data = nullptr;

	// 배열에 저장된 항목의 수.
	int size = 0;

	// 배열 저장 공간의 크기.
	int capacity = 2;
};