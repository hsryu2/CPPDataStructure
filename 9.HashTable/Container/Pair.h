#pragma once

// 템플릿 특수화(구체화?).

// 키-값을 쌍으로 저장할 때 사용할 자료형.
template<typename KeyType, typename ValueType>
class Pair
{
public:
	// 키 타입의 데이터 저장 변수.
	KeyType key;

	// 값 타입의 데이터 저장 변수.
	ValueType value;

	Pair()
		: key(), value()
	{
	}

	Pair(const KeyType& key, const ValueType& value)
		: key(key), value(value)
	{
	}

	// 연산자 오버로딩.
	bool operator==(const Pair<KeyType, ValueType>& other)
	{
		// 전제 조건: key와 value 각각 비교가 가능해야 함.
		return key == other.key && value == other.value;
	}

	bool operator!=(const Pair<KeyType, ValueType>& other)
	{
		// 전제 조건: key와 value 각각 비교가 가능해야 함.
		return !(*this == other);
	}

	bool operator>(const Pair<KeyType, ValueType>& other)
	{
		return key > other.key;
	}

	bool operator<(const Pair<KeyType, ValueType>& other)
	{
		return key < other.key;
	}

	bool operator>=(const Pair<KeyType, ValueType>& other)
	{
		return key >= other.key;
	}

	bool operator<=(const Pair<KeyType, ValueType>& other)
	{
		return key <= other.key;
	}
};