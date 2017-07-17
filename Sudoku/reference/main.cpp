#include "grid.h"
#include <algorithm>
#include <Windows.h>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1, c2;
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	QueryPerformanceCounter(&large_interger);

	c1 = large_interger.QuadPart;
	grid g;         // Create new grid object and ask for solution
	g.search();     // Find and print out solution
	
	QueryPerformanceCounter(&large_interger);
	c2 = large_interger.QuadPart;
	cout << "time = " << (c2 - c1) * 1000 / dff << "ms" << endl;

	std::cout << std::endl << "Here is the solution :: " << std::endl << std::endl;
	g.print();

	system("pause");
	return 0;
}