#include "HashTable.h"
#include <iostream>

// 해시 함수(Hash Function)
// 키를 어떠한 과정을 통해서 숫자로 변환해주는 함수.
// 여기에 붙이는 static은 전역이 아니라 private의 의미.
static int GenerateHash(const std::string& keyString)
{

    
    // 출력할 해시 변수 선언.
    // "ABCD" [A,B,C,D] = [65, 66, 67, 68]
    // "ABCD" == "DCBA"
    int hash = 0;

    // 문자열을 문자 배열로 활용해 해시 생성.
    const int length = static_cast<int>(keyString.length());
    for (int i = 0; i < length; i++)
    {
        // 해시 생성 로직
        // hash += keyString[i] * (i + 1); // -> 성능이 좋지 않음.
        // Java의 방식. Hornor' Method.
        hash = hash * 31 + keyString[i]; 
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
    int buketIndex = GenerateHash(key) % bucketCount;

    // 저장할 배열 선택.
    std::vector<Entry>& position = table[buketIndex];

    // 중복된 키가 있는지 확인 후 없으면 추가.
    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
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
    int buketIndex = GenerateHash(key) % bucketCount;

    // 저장할 배열 선택.
    std::vector<Entry>& position = table[buketIndex];

    // 중복된 키가 있는지 확인 후 있으면 추가.
    const int length = static_cast<int>(position.size());

    // 순차 탐색
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
        {
            // 해당 키를 갖는 데이터를 2차 자료구조에서 제거.
            position.erase(position.begin() + i);
            return true;
        }
    }

        // 원하는 키를 갖는 데이터를 찾지 못함 - 삭제 실패.
    return false;
}

bool HashTable::Find(const std::string& key, Entry& outEntry)
{
    // 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
    int buketIndex = GenerateHash(key) % bucketCount;

    // 저장할 배열 선택.
    std::vector<Entry>& position = table[buketIndex];

    // 예외처리 - 2차 자료구조에 저장된 데이터가 없으면 실패.
    if (position.size() == 0)
    {
        return false;
    }

    // 중복된 키가 있는지 확인 후 있으면 추가.
    const int length = static_cast<int>(position.size());

    // 순차 탐색
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
        {
            // 출력용 변수에 값 할당.
            outEntry = position[i];
            return true;
        }
    }
    return false;
}


// 출력함수
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
                << "key: " << item.key
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
    for (auto& container : table)
    {
        // 2차 자료구조의 저장된 데이터 수를 합산.
        sum += static_cast<int>(container.size());
    }

    // 합산된 값이 0인지 비교.
    return sum == 0;
}