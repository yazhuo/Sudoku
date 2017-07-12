#include <iostream>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

bool sign = false;
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

void Construct(int blank);
void Output();
bool Check(int n, int key);
int DFS(int n);

int main(int argc, char* argv[])
{
	int blank;
	cout << "please input the number of blanks : ";
	cin >> blank;

	Construct(blank);
	Output();
	DFS(0);
	cout << "after solving..." << endl;
	Output();
	system("pause");
	return 0;
}

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
}

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