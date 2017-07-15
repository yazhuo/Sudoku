#include "dfs.h"
#include "sudoku.h"

bool sign = false;

bool Check(int n, int key)
{
	/*�ж�n���ں����Ƿ�Ϸ�*/
	for (int i = 0; i < 9; i++)
	{
		int j = n / 9;
		if (sudoku[j][i] == key)
			return false;
	}

	/*�ж�n���������Ƿ�Ϸ�*/
	for (int i = 0; i < 9; i++)
	{
		int j = n % 9;
		if (sudoku[i][j] == key)
			return false;
	}

	int x = n / 9 / 3 * 3;
	int y = n % 9 / 3 * 3;

	/*�ж�n���ڵ�С�Ź����Ƿ�Ϸ�*/
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
	/*���еĶ����ϣ��˳��ݹ�*/
	if (n > 80)
	{
		sign = true;
		return 0;
	}

	/*��ǰλ��Ϊ��ʱ����*/
	if (sudoku[n / 9][n % 9] != 0)
	{
		DFS(n + 1);
	}
	else
	{
		/*����Ե�ǰλ����ö�ٲ���*/
		for (int i = 1; i <= 9; i++)
		{
			/*��������ʱ��������*/
			if (Check(n, i) == true)
			{
				sudoku[n / 9][n % 9] = i;
				/*��������*/
				DFS(n + 1);
				if (sign == true)
					return 0;
				sudoku[n / 9][n % 9] = 0;
			}
		}
	}
	return 0;
}