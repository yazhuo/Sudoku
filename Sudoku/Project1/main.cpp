#include <iostream>
#include <Windows.h>
#include "coord.h"
#include "cell.h"

using std::cout;
using std::endl;

#define SIZE 9
Cell cells[SIZE][SIZE];//�洢ÿ��������ϸ��Ϣ������������ӵ��к�������

bool GenerateValidMatrix();
vector<int> getValidValuevector(Coord);
void nextCoord(Coord & coCurrent);
void preCoord(Coord & coCurrent);

int main(int argc, char* argv[])
{
	DWORD begin, end;
	begin = GetTickCount();
	GenerateValidMatrix();
	end = GetTickCount();
	cout << "time = " << (end - begin) << "ms"<< endl;

	//�������õ���������
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << cells[i][j].value << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

bool GenerateValidMatrix()
{
	Coord coCurrent;
	coCurrent.x = 0;
	coCurrent.y = 0;

	while (true)
	{
		Cell &c = cells[coCurrent.x][coCurrent.y];
		//cout << coCurrent.x << " " << coCurrent.y << endl;
		vector<int> al;
		//��ǰ����δ�������
		if (!c.isProcessed)
		{
			//��õ�ǰ���ӵĿ�ȡֵ����
			al = getValidValuevector(coCurrent);
			c.validvector = al;
		}
		//��ǰ���ӵĿ�ȡֵ��������0
		if (c.validvector.size() > 0)
		{
			//����ȡ��һ����ȡֵ��������ǰ�ĸ���
			c.pickNextValidValue();
			//�����ҵ����һ������
			if (coCurrent.x == SIZE - 1 && coCurrent.y == SIZE - 1)
				return true;
			else
				nextCoord(coCurrent);
		}
		else
		{
			//����ص��˵�һ������
			if (coCurrent.x == 0 && coCurrent.y == 0)
				return false;
			else
			{
				//�����ǰ���ӵ�������Ϣ
				c.Clear();
				preCoord(coCurrent);
			}
		}
	}
	return true;
}

vector<int> getValidValuevector(Coord co)
{
	bool flag[9] = { 0 };
	vector<int> al;
	for (int i = 0; i < SIZE; i++)
	{
		if (cells[i][co.y].value > 0)
			flag[cells[i][co.y].value - 1] = true;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (cells[co.x][i].value > 0)
			flag[cells[co.x][i].value - 1] = true;
	}
	for (int i = co.x / 3 * 3; i < co.x / 3 * 3 + 3; ++i)
	{
		for (int j = co.y / 3 * 3; j < co.y / 3 + 3; ++j)
		{
			if (cells[i][j].value > 0)
				flag[cells[i][j].value - 1] = true;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (flag[i] == false)
			al.push_back(i + 1);
	}
	return al;
}

void nextCoord(Coord & co)
{
	co.y++;
	if (co.y >= 9)
	{
		co.y = 0;
		co.x++;
	}
}

void preCoord(Coord & co)
{
	co.y--;
	if (co.y < 0)
	{
		co.y = 8;
		co.x--;
	}
}