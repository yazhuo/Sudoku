#include <iostream>
#include <Windows.h>
#include "coord.h"
#include "cell.h"

using std::cout;
using std::endl;

#define SIZE 9
Cell cells[SIZE][SIZE];//存储每个格子详细信息，索引代表格子的行和列坐标

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

	//输出构造好的数独问题
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
		//当前格子未被处理过
		if (!c.isProcessed)
		{
			//获得当前格子的可取值链表
			al = getValidValuevector(coCurrent);
			c.validvector = al;
		}
		//当前格子的可取值个数大于0
		if (c.validvector.size() > 0)
		{
			//从中取出一个可取值并赋给当前的格子
			c.pickNextValidValue();
			//当查找到最后一个格子
			if (coCurrent.x == SIZE - 1 && coCurrent.y == SIZE - 1)
				return true;
			else
				nextCoord(coCurrent);
		}
		else
		{
			//如果回到了第一个格子
			if (coCurrent.x == 0 && coCurrent.y == 0)
				return false;
			else
			{
				//清楚当前格子的所有信息
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