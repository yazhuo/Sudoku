#include <iostream>
#include <ctime>
#include "dfs.h"
#include "sudoku.h"

using std::cin;
using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
	int blank;
	cout << "please input the number of blanks : ";
	cin >> blank;

	Construct(blank);
	cout << "before solving..." << endl;
	Output();

	/*Çó½âÊý¶À*/
	DFS(0);

	cout << "after solving..." << endl;
	Output();

	system("pause");
	return 0;
}