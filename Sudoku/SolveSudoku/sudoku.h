#ifndef SUDOKU_H
#define SUDOKU_H

#include <ctime>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

int sudoku[9][9] = {
	{ 7,2,9,5,3,4,8,6,1 },
	{ 5,3,4,8,6,1,7,2,9 },
	{ 8,6,1,7,2,9,5,3,4 },
	{ 2,9,7,3,4,5,6,1,8 },
	{ 3,4,5,6,1,8,2,9,7 },
	{ 6,1,8,2,9,7,3,4,5 },
	{ 9,7,2,4,5,3,1,8,6 },
	{ 4,5,3,1,8,6,9,7,2 },
	{ 1,8,6,9,7,2,4,5,3 }
};

void Construct(int b)
{
	srand(time(NULL));
	for (int i = 0; i < b; i++)
	{
		int pos = rand() % 81;
		sudoku[pos / 9][pos % 9] = 0;
	}
}

void Output()
{
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
			if (j % 3 == 2)
				cout << " ";
		}
		cout << endl;
		if (i % 3 == 2)
		{
			cout << endl;
		}
	}
}

#endif // !SUDOKU_H