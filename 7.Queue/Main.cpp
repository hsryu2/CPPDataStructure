#include "Container/Queue.h"

int main()
{
	// 큐 객체 생성.
	Queue<int> queue;
	const int count = 10;
	for (int i = 0; i < count; i++)
	{
		queue.Enqueue(i+1);
		
	}

	queue.Print();

	// 값 추출.
	int value;
	queue.Dequeue(value);
	queue.Dequeue(value);
	queue.Dequeue(value);

	queue.Print();

	queue.Enqueue(11);
	queue.Enqueue(12);
	queue.Enqueue(13);

	std::cin.get();
	
}