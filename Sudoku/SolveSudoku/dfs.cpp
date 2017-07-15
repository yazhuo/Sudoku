#include "dfs.h"
#include "sudoku.h"

bool sign = false;

bool Check(int n, int key)
{
	/*判断n所在横列是否合法*/
	for (int i = 0; i < 9; i++)
	{
		int j = n / 9;
		if (sudoku[j][i] == key)
			return false;
	}

	/*判断n所在竖列是否合法*/
	for (int i = 0; i < 9; i++)
	{
		int j = n % 9;
		if (sudoku[i][j] == key)
			return false;
	}

	int x = n / 9 / 3 * 3;
	int y = n % 9 / 3 * 3;

	/*判断n所在的小九宫格是否合法*/
	for (int i = x; i < x + 3; i++)
	{
		for (int j = y; j < y + 3; j++)
		{
			if (sudoku[i][j] == key)
				return false;
		}
	}

	return true;
}

int DFS(int n)
{
	/*所有的都符合，退出递归*/
	if (n > 80)
	{
		sign = true;
		return 0;
	}

	/*当前位不为空时跳过*/
	if (sudoku[n / 9][n % 9] != 0)
	{
		DFS(n + 1);
	}
	else
	{
		/*否则对当前位进行枚举测试*/
		for (int i = 1; i <= 9; i++)
		{
			/*满足条件时填入数字*/
			if (Check(n, i) == true)
			{
				sudoku[n / 9][n % 9] = i;
				/*继续搜索*/
				DFS(n + 1);
				if (sign == true)
					return 0;
				sudoku[n / 9][n % 9] = 0;
			}
		}
	}
	return 0;
}