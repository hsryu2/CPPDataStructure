#include "Container/Queue.h"

int main()
{
	// 큐 객체 생성.
	Queue<int> queue;
	const int count = 10;
	for (int ix = 0; ix < count; ++ix)
	{
		queue.Enqueue(ix + 1);
	}

	// 출력.
	queue.Print();

	// 값 추출.
	int value;
	queue.Dequeue(value);
	queue.Dequeue(value);
	queue.Dequeue(value);

	queue.Print();

	// 값 추가.
	queue.Enqueue(11);
	queue.Enqueue(12);
	queue.Enqueue(13);
	queue.Enqueue(14);

	std::cin.get();
}