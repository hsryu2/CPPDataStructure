#include "Container/Stack.h"
#include <iostream>
#include <time.h>

// 랜덤(정수).
int RandomRange(int min, int max)
{
	int diff = (max - min) + 1;
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

// 랜덤(부동소수).
float RandomRange(float min, float max)
{
	float percent
		= static_cast<float>(rand())
		/ static_cast<float>(RAND_MAX);
	float diff = (max - min);
	return (percent * diff) + min;
}

int main()
{
	// 랜덤 시드.
	srand(time(nullptr));

	// 스택 생성.
	const int count = 10;
	Stack<float, count> stack;

	// 데이터 추가.
	for (int ix = 0; ix < count + 1; ++ix)
	{
		if (!stack.Push(RandomRange(100.0f, 200.0f)))
		{
			// 예외 처리...
			std::cout << "스택에 값 추가 실패\n";
		}
	}

	// 스택에서 값 빼오면서 출력.
	const int stackCount = stack.Count();
	for (int ix = 0; ix < stackCount; ++ix)
	{
		float value = 0.0f;
		if (stack.Pop(value))
		{
			std::cout << value << "\n";
		}
	}

	std::cin.get();
}