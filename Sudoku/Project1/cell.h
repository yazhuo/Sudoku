#ifndef CELL_H
#define CELL_H
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>
using std::vector;

//代表每个格子的详细信息
class Cell
{
public:
	vector<int> validvector; //可取值的数据
	int value; //格子的值
	bool isProcessed;

	Cell()
	{
		value = 0;
		isProcessed = false;
	}

	void Clear()
	{
		validvector.clear();
		value = 0;
		isProcessed = false;
	}

	void pickNextValidValue()
	{
		srand(time(NULL));
		vector<int>::iterator it = validvector.begin();
		int random = (int)rand() % validvector.size();
		value = *(it + random);
		validvector.erase(it + random);
		isProcessed = true;		
	}
};

#endif