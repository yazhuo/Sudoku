#include <iostream>
#include "dfs.h"
#include "grid.h"
#include "sudoku.h"

using std::cin;
using std::cout;
using std::endl;



int main(int argc, char* argv[])
{
	//
	//cout << "before solving..." << endl;
	////dfs_Output();
	//dancing_Output();

	///*�������*/
	///*1. ������ȷ���*/
	////DFS(0);
	///*2. �赸��*/
	////dancing_links();

	//cout << "after solving..." << endl;
	////dfs_Output();
	//dancing_Output(); 
	//

	grid g;
	if (g.search())
	{
		g.print();
	}
	else
	{
		cout << "wrong..." << endl;
	}
	

	system("pause");
	return 0;
}