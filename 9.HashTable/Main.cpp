#include "Container/HashTable.h"
#include <iostream>


int main()
{
	// 해시 테이블 객체 생성.
	HashTable table;

	// 데이터 추가.
	table.Add("YHS", "010-1234-5678");
	table.Add("YHS", "010-3456-2346");
	table.Add("QQQ", "010-4567-5774");
	table.Add("WWW", "010-5456-5647");
	table.Add("EEE", "010-8568-3456");
	table.Add("RRR", "010-7777-8888");

	//출력
	table.Print();

	// 검색
	Pair<std::string, std::string> outValue;
	if (table.Find("YHS", outValue))
	{
		std::cout
			<< "검색 성공. Key:  " << outValue.key
			<< "| Value: " << outValue.value << "\n";
	}

	// 삭제
	table.Delete("QQQ");
	table.Delete("WWW");

	table.Print();

	std::cin.get();

}