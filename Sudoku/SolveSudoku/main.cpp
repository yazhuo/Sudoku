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