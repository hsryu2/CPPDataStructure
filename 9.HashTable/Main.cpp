#include "Container/HashTable.h"
#include <iostream>

int main()
{
	// 해시 테이블 객체 생성.
	HashTable table;

	// 데이터 추가.
	table.Add("Ronnie", "010-12345678");
	table.Add("Ronnie", "010-36453766");
	table.Add("Kevin", "010-32898734");
	table.Add("Baker", "010-23984798");
	table.Add("Emily", "010-21938478");
	table.Add("Taejun", "010-12093804");

	// 출력.
	table.Print();

	// 검색.
	Pair<std::string, std::string> outValue;
	if (table.Find("Baker", outValue))
	{
		std::cout
			<< "검색 성공. Key: " << outValue.key
			<< " | Value: " << outValue.value << "\n";
	}

	// 삭제.
	table.Delete("Ronnie");
	table.Delete("Kevin");

	table.Print();

	std::cin.get();
}