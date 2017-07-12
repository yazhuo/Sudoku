#ifndef CELL_H
#define CELL_H
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>
using std::vector;

//����ÿ�����ӵ���ϸ��Ϣ
class Cell
{
public:
	vector<int> validvector; //��ȡֵ������
	int value; //���ӵ�ֵ
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