#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

int matrix[3][3];
int sudoku[9][9] = { 0 };

//利用置换的方法组合数独
void permuteMatrix();

int main(int argc, char *argv[])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = i * 3 + j + 1;
		}
	}

	/*随机初始化矩阵*/
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		int temp = rand() % 9;
		int j = matrix[i / 3][i % 3];
		matrix[i / 3][i % 3] = matrix[temp / 3][temp % 3];
		matrix[temp / 3][temp % 3] = j;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	permuteMatrix();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

void permuteMatrix()
{
	//设置B5，根据B5置换B3和B6
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sudoku[i + 3][j + 3] = matrix[i][j];   
			if (i == 0)
			{
				sudoku[i + 5][j + 6] = sudoku[i + 3][j + 3];
				sudoku[i + 4][j] = sudoku[i + 3][j + 3];
			}
			else if (i == 1)
			{
				sudoku[i + 2][j + 6] = sudoku[i + 3][j + 3];
				sudoku[i + 4][j] = sudoku[i + 3][j + 3];
			}
			else
			{
				sudoku[i + 2][j + 6] = sudoku[i + 3][j + 3];
				sudoku[i + 1][j] = sudoku[i + 3][j + 3];
			}
		}
	}

	//根据B5置换B2和B8
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (j == 0)
			{
				sudoku[i][j + 4] = sudoku[i + 3][j + 3];
				sudoku[i + 6][j + 5] = sudoku[i + 3][j + 3];
			}
			else  if (j == 1)
			{
				sudoku[i][j + 4] = sudoku[i + 3][j + 3];
				sudoku[i + 6][j + 2] = sudoku[i + 3][j + 3];
			}
			else
			{
				sudoku[i][j + 1] = sudoku[i + 3][j + 3];
				sudoku[i + 6][j + 2] = sudoku[i + 3][j + 3];
			}
		}
	}

	//根据B4置换B1和B7
	for (int j = 0; j<3; ++j)
	{
		for (int i = 0; i<3; ++i)
		{
			if (0 == j)
			{
				sudoku[i][j + 1] = sudoku[i + 3][j];
				sudoku[i + 6][j + 2] = sudoku[i + 3][j];
			}
			else if (1 == j)
			{
				sudoku[i][j + 1] = sudoku[i + 3][j];
				sudoku[i + 6][j - 1] = sudoku[i + 3][j];
			}
			else
			{
				sudoku[i][j - 2] = sudoku[i + 3][j];
				sudoku[i + 6][j - 1] = sudoku[i + 3][j];
			}

		}
	}

	//根据B6置换B3和B9
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (0 == j)
			{
				sudoku[i][j + 7] = sudoku[i + 3][j + 6];
				sudoku[i + 6][j + 8] = sudoku[i + 3][j + 6];
			}
			else if (1 == j)
			{
				sudoku[i][j + 7] = sudoku[i + 3][j + 6];
				sudoku[i + 6][j + 5] = sudoku[i + 3][j + 6];
			}
			else
			{
				sudoku[i][j + 4] = sudoku[i + 3][j + 6];
				sudoku[i + 6][j + 5] = sudoku[i + 3][j + 6];
			}
		}
	}
}