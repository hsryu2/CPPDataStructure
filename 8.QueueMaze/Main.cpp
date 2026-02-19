#include <iostream>
#include "Container/Queue.h"
#include "Location2D.h"		
#include <Windows.h>	// 콘솔 제어을 위해 활용.

// 맵 (미로).
// 작은 맵.
//const int MAZE_SIZE = 6;
//char map[MAZE_SIZE][MAZE_SIZE] = // [row][col]
//{
//	// e = 시작위치 , x = 탈출구, 1 = 벽, 0 = 갈수있는곳
//	// e, 1은 갈 수 없음. 0, x 움직일 수 있음.
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

//큰 맵.
const int MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'e', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'x'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

// 방문하려는 위치가 유효한지 확인하는 함수.
bool IsValidLocation(const Location2D& location)
{
	// 편의 목적.
	const int row = location.row;
	const int col = location.col;

	// 인덱스 범위 확인.
	if (row < 0 || col < 0 || row >= MAZE_SIZE || col >= MAZE_SIZE)
	{
		return false;
	}
	
	// 이동하려는 곳이 이동 가능한지 확인.
	return map[row][col] == '0' || map[row][col] == 'x';

}

// 콘솔 화면 지우는 함수.
void ClearScreen()
{
	// 콘솔 명령어 cls 실행.
	system("cls");
}

// 텍스트 색상 지정 함수.
void SetConsoleColor(WORD color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		color
	);
}

// 맵 그리는 함수.
void PrintMap(const Location2D& playerPosition, DWORD delay)
{
	// 쓰레드 재우는 함수(단위: 밀리초 = 1/1000초).
	Sleep(delay);

	// 콘솔 화면 지우기.
	//ClearScreen();
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);

	// 맵 순회하면서 그리기.
	for (int row = 0; row < MAZE_SIZE; ++row)
	{
		for (int col = 0; col < MAZE_SIZE; ++col)
		{
			// 플레이어 출력.
			if (row == playerPosition.row
				&& col == playerPosition.col)
			{
				SetConsoleColor(FOREGROUND_GREEN);
				std::cout << "P ";
				SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				continue;
			}

			// 목표 위치 출력.
			if (map[row][col] == 'x')
			{
				SetConsoleColor(FOREGROUND_RED);
				std::cout << "x ";
				SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				continue;
			}

			// 맵 출력.
			std::cout << map[row][col] << " ";
		}

		std::cout << "\n";
	}
}

int main()
{
	// 커서끄기
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// 시작 위치 검색.
	Location2D start;

	bool found = false;
	for (int row = 0; row < MAZE_SIZE; ++row)
	{
		for (int col = 0; col < MAZE_SIZE; ++col)
		{
			if (map[row][col] == 'e')
			{
				start.row = row;
				start.col = col;
				found = true;
				break;
			}
		}

		// 찾았으면 루프 종료.
		if (found)
		{
			break;
		}
	}

	// 초기 맵 출력.
	PrintMap(start, 0);

	// 큐 생성.
	Queue<Location2D, MAZE_SIZE> queue;

	// 시작 위치 큐에 추가.
	queue.Enqueue(start);

	// 길찾기 (BFS).
	// 큐에 비어있지 않으면 = 방문할 위치가 남아 있으면.
	// 방문 및 길찾기 진행.
	while (!queue.IsEmpty())
	{
		// 방문할 위치 꺼내기.
		Location2D current;
		if (!queue.Dequeue(current))
		{
			break;
		}

		// 위치 출력.
		PrintMap(current, 500);

		// 출구에 도착했는지 확인.
		if (map[current.row][current.col] == 'x')
		{
			std::cout << "\n 미로 탐색 성공\n";
			return 0;
		}

		// 방문 및 방문한 위치 표시.
		map[current.row][current.col] = '.';

		// 방문할 지점 큐에 추가.
		// 큐에 넣을 순서는 정할 수 있음.
		// 상/하/좌/우 순서로 큐에 삽입.
		if (IsValidLocation(
			Location2D(current.row - 1, current.col)))
		{
			queue.Enqueue(Location2D(current.row - 1, current.col));
		}

		if (IsValidLocation(
			Location2D(current.row + 1, current.col)))
		{
			queue.Enqueue(Location2D(current.row + 1, current.col));
		}

		if (IsValidLocation(
			Location2D(current.row, current.col - 1)))
		{
			queue.Enqueue(Location2D(current.row, current.col - 1));
		}

		if (IsValidLocation(
			Location2D(current.row, current.col + 1)))
		{
			queue.Enqueue(Location2D(current.row, current.col + 1));
		}

	}

	// 길찾기 실패.
	std::cout << "미로 탐색 실패.\n";


}