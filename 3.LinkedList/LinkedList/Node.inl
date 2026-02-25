#include "Node.h"

// .inl -> inline 약자.
// 예전에 템플릿 코드의 선언/구현을 명시적 파일로 분리할 때 
// 주로 활용했던 기법.
// 최근에 잘 사용하지 않음.

template<typename T>
Node<T>::Node()
	: data(), next(nullptr)
{
}

template<typename T>
Node<T>::Node(T data)
	: data(data), next(nullptr)
{
}
