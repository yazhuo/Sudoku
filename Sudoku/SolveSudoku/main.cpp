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

	///*求解数独*/
	///*1. 深度优先方法*/
	////DFS(0);
	///*2. 舞蹈链*/
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