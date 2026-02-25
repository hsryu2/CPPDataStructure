#pragma once

// 행렬 좌표를 관리하는 클래스.
class Location2D
{
public:
	// 행 (세로).
	int row = 0;
	// 열 (가로).
	int col = 0;

public:
	Location2D(int row = 0, int col = 0)
		: row(row), col(col)
	{
	}
};