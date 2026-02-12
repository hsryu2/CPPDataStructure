// 쟤네 둘이 같이 쓸라고 하면 같은거 2번 선언했다고 헤더충돌이 생겨 컴파일러가 뭐라함
// 따라서 LEAN AND MEAN으로 예외처리해줌.

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <winsock2.h>

#include <iostream>
#include <cassert>
#include <array>

// 템플릿으로 배열 만들기.
template<typename T, size_t size = 5> // 기본값 넣기도 가능.
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
		assert(false);

		// 인덱스 범위 확인.
		if (index < 0 || index >= size)
		{
			// 어써트(꼭 검증이 필요한 구문에 활용)
			// 디버그 모드에서만 동작.
			
			__debugbreak();
		}
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

private:
	// 배열 변수
	T data[size] = {};
};

int main()
{

	// 배열 변수 선언.
	Array<int, 20> array;
	array[3] = 20;
	
	// const 접근.
	const auto& arrayReference = array[1];
	
	
	std::cin.get();


}