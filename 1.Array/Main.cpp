#include <iostream>
#include <cassert>
#include <array>

// 템플릿으로 배열 만들기.
template<typename T, size_t size = 5>
class Array
{
public:
	size_t Size() const
	{
		return size;
	}

	// 배열 연산자 오버로딩.
	T& operator[](size_t index)
	{
		// 어써트(꼭 검증이 필요한 구문에 활용).
		// 디버그 모드에서만 동작.
		assert(index < 0 || index >= size);

		// 인덱스 범위 확인.
		//if (index < 0 || index >= size)
		//{
		//	__debugbreak();
		//}

		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

private:
	// 배열 변수.
	T data[size] = {};
};

int main()
{
	// 배열 변수 선언.
	Array<int, 5> array;
	array[3] = 20;

	// const 접근.
	const auto& arrayReference = array;

	std::cin.get();
}