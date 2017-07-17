#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <Windows.h>
#include "sudoku.h"

using std::cout;
using std::endl;

int main()
{
	cout << "before solving..." << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i * 9 + j] << " ";
		}
		cout << endl;
	}

	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1, c2;
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;

	solve_sudoku_dancing_links();

	QueryPerformanceCounter(&large_interger);
	c2 = large_interger.QuadPart;
	cout << "time = " << (c2 - c1) * 1000 / dff << "ms" << endl;

	cout << "after solving..." << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i * 9 + j] << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}