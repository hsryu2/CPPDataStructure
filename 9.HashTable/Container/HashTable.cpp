#include "HashTable.h"
#include <iostream>

// 해시 함수(Hash Function).
// 키를 어떠한 과정을 통해서 숫자로 변환해주는 함수.
// 여기에 붙이는 static은 전역이 아니라 private의 의미.
static int GenerateHash(const std::string& keyString)
{
	// 출력할 해시 변수 선언.
	// "ABCD" [A,B,C,D] = [65,66,67,68]
	// "ABCD" == "DCBA"
	int hash = 0;

	// 문자열을 문자 배열로 활용해 해시 생성.
	const int length = static_cast<int>(keyString.length());
	for (int ix = 0; ix < length; ++ix)
	{
		// 해시 생성 로직.
		//hash += keyString[ix] * (ix + 1); // -> 성능이 좋지는 않음.
		// Java의 방식. Hornor' Method.
		hash = hash * 31 + keyString[ix];
	}

	// 생성한 해시 값 반환.
	// 오버플로우로 인한 음수 변환 가능성이 있기 때문에 절대값으로 반환.
	return std::abs(hash);
}

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

bool HashTable::Add(const std::string& key, const std::string& value)
{
	// 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
	int bucketIndex = GenerateHash(key) % bucketCount;

	// 저장할 동적 배열(2차 자료구조) 선택.
	std::vector<Entry>& position = table[bucketIndex];

	// 중복된 키가 있는지 확인 후 없으면 추가.
	const int length = static_cast<int>(position.size());

	// 순차 탐색(처음부터 일일이 하나씩 검색하는 방법).
	for (int ix = 0; ix < length; ++ix)
	{
		// 중복된 키값 확인.
		if (position[ix].key == key)
		{
			// 중복된 키 허용 안함.
			return false;
		}
	}

	// 중복된 키가 없다면 자료 추가.
	position.emplace_back(Entry(key, value));
	return true;
}

bool HashTable::Delete(const std::string& key)
{
	// 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
	int bucketIndex = GenerateHash(key) % bucketCount;

	// 저장할 동적 배열(2차 자료구조) 선택.
	std::vector<Entry>& position = table[bucketIndex];

	// 중복된 키가 있는지 확인 후 있으면 삭제.
	const int length = static_cast<int>(position.size());

	// 순차 탐색(처음부터 일일이 하나씩 검색하는 방법).
	for (int ix = 0; ix < length; ++ix)
	{
		// 중복된 키값 확인.
		if (position[ix].key == key)
		{
			// 해당 키를 갖는 데이터를 2차 자료구조에서 제거.
			position.erase(position.begin() + ix);
			return true;
		}
	}

	// 원하는 키를 갖는 데이터를 찾지 못함 - 삭제 실패.
	return false;
}

bool HashTable::Find(const std::string& key, Entry& outEntry)
{
	// 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
	int bucketIndex = GenerateHash(key) % bucketCount;

	// 저장할 동적 배열(2차 자료구조) 선택.
	std::vector<Entry>& position = table[bucketIndex];

	// 예외처리 - 2차 자료구조에 저장된 데이터가 없으면 실패.
	if (position.size() == 0)
	{
		return false;
	}

	// 중복된 키가 있는지 확인.
	const int length = static_cast<int>(position.size());

	// 순차 탐색(처음부터 일일이 하나씩 검색하는 방법).
	for (int ix = 0; ix < length; ++ix)
	{
		// 중복된 키값 확인.
		if (position[ix].key == key)
		{
			// 출력용 변수에 값 할당.
			outEntry = position[ix];
			return true;
		}
	}

	// 원하는 키를 갖는 데이터를 찾지 못하면 검색 실패.
	return false;
}

// 출력 함수.
void HashTable::Print()
{
	// 모든 자료를 출력.
	for (const auto& container : table)
	{
		// 2차 자료구조에 저장된 데이터가 없으면 건너뛰기.
		if (container.size() == 0)
		{
			continue;
		}

		// 데이터가 있으면 출력.
		for (const auto& item : container)
		{
			std::cout
				<< "Key: " << item.key
				<< " | Value: " << item.value
				<< "\n";
		}
	}
}

// Getter.
bool HashTable::IsEmpty() const
{
	// 배열 - 2차 자료구조 전체에 저장된 데이터가 없는지 확인.
	int sum = 0;
	for (const auto& container : table)
	{
		// 2차 자료구조의 저장된 데이터 수를 합산.
		sum += static_cast<int>(container.size());
	}

	// 합산한 값이 0인지 비교.
	return sum == 0;
}