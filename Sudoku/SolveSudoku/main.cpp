#include <iostream>
#include <Windows.h>
#include "dfs.h"
#include "grid.h"
#include "sudoku.h"

using std::cin;
using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
	
	cout << "before solving..." << endl;
	dfs_Output();

	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1, c2;
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;
	
	/*求解数独*/
	/*深度优先方法*/
	DFS(0);

	QueryPerformanceCounter(&large_interger);
	c2 = large_interger.QuadPart;
	cout << "time = " << (c2-c1)*1000 / dff << "ms" << endl;

	cout << "after solving..." << endl;
	dfs_Output();

	system("pause");
	return 0;
}