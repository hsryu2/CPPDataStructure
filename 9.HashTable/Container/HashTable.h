#pragma once

#include "Pair.h"
#include <vector>
#include <string>

// 해시테이블 클래스.
class HashTable
{
private:
	// 장황한 타입을 Entry로 치환.
	using Entry = Pair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

private:
	// 내부 저장소 크기.
	// - 내부 저장소 크기는 소수(1과 자기자신으로만 나눠지는 수)를
	// 선택하는게 해시 충돌 방지에 좋음.
	// 사용 가능한 소수 중에서 큰 수를 사용.

	static const int bucketCount = 19;

	// 이차 저장소(해시 충돌 해결 방법으로 체이닝(Chaining).
	std::vector<Entry> table[bucketCount];

};