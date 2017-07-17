#include "grid.h"
#include <iostream>

/** Constructor for the grid class
@post The matrix is initialized with data objects in
correct positions, linked within itself, to the
column array and to the header pointer, and the
clues inputed by the user are processed.
*/
grid::grid()
{
	// The output array is initialized along with its size
	size = 0;
	output = new data*[MAX_ROWS];
	// Memory is allocated for the data matrix and column array
	matrix = new data**[MAX_ROWS];
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		matrix[i] = new data*[MAX_COLS];
		for (int j = 0; j < MAX_COLS; ++j)
			matrix[i][j] = nullptr;
	}
	columns = new column*[MAX_COLS];

	// Fill the column array with column objects
	for (int i = 0; i < MAX_COLS; ++i)
		columns[i] = new column;
	// Link the column arrays together and set their variables
	for (int i = 0; i < MAX_COLS; ++i)
	{
		if (i == 0)
		{
			columns[i]->left = &header;
			columns[i]->right = columns[i + 1];
		}
		else if (i == MAX_COLS - 1)
		{
			columns[i]->left = columns[i - 1];
			columns[i]->right = &header;
		}
		else
		{
			columns[i]->left = columns[i - 1];
			columns[i]->right = columns[i + 1];
		}
		columns[i]->size = 0;
		columns[i]->up = columns[i];
		columns[i]->down = columns[i];
		columns[i]->col = columns[i];
		columns[i]->name = i;
		columns[i]->row = NULL;
	}
	// Connect the header to the column array
	header.right = columns[0];
	header.left = columns[MAX_COLS - 1];

	// Populate the sparse matrix with data objects
	initMatrix();

	// Link the data objects to the next object in the matrix
	// to the left and right, skipping over nullptrs
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		int size = 0;
		data** row = new data*[MAX_COLS];
		for (int j = 0; j < MAX_COLS; ++j)
		{
			if (matrix[i][j] != nullptr)
			{
				row[size] = matrix[i][j];
				++size;
			}
		}
		for (int x = 0; x < size; ++x)
		{
			if (x == 0)
			{
				row[x]->left = row[size - 1];
				row[x]->right = row[x + 1];
			}
			else if (x == size - 1)
			{
				row[x]->left = row[x - 1];
				row[x]->right = row[0];
			}
			else
			{
				row[x]->left = row[x - 1];
				row[x]->right = row[x + 1];
			}
		}
		delete[] row;
	}
	// Link the data objects to the next object in the matrix
	// to the left and right, skipping over nullptrs and
	// linking the top and bottom to the column array
	for (int j = 0; j< MAX_COLS; ++j)
	{
		int size = 1;
		data** col = new data*[MAX_ROWS + 1];
		col[0] = columns[j];
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			if (matrix[i][j] != nullptr)
			{
				col[size] = matrix[i][j];
				++size;
				matrix[i][j]->col = columns[j];
				++(columns[j]->size);
			}
		}
		for (int x = 0; x < size; ++x)
		{
			if (x == 0)
			{
				col[x]->up = col[size - 1];
				col[x]->down = col[x + 1];
			}
			else if (x == size - 1)
			{
				col[x]->up = col[x - 1];
				col[x]->down = col[0];
			}
			else
			{
				col[x]->up = col[x - 1];
				col[x]->down = col[x + 1];
			}
		}
		delete[] col;
	}

	// Gets the clues from the user before solving the sudoku
	askUser();

}

/** Destructor for the grid class
@post Every dynamically alocated variable, including the
elements of the sparse array, is delete from the
heap before the grid is removed
*/
grid::~grid()
{
	// Delete every item in each row, then delete the row
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int x = 0; x < MAX_COLS; ++x)
			delete matrix[i][x];
		delete[] matrix[i];
	}
	delete[] matrix;
	// Delete each column item
	for (int i = 0; i < MAX_COLS; ++i)
		delete columns[i];
	delete[] columns;
	delete[] output;
}

/** Parses input from the user on which spots are filled
@param n The number at the spot on the grid
@param r The row of the spot on the grid
@param c The column of the spot on the grid
@post coverClue is called on one of the corresponding
data members in the matrix to the given row
*/
void grid::parseInput(int n, int r, int c)
{
	// Finds which row in the matrix has to be covered
	// from the given row, column and number value
	int row = ((r - 1) * 81) + ((c - 1) * 9) + (n - 1);
	coverClue(matrix[row][row / 9]);
}

/** Depth first recursive search to find solution to the sudoku
@return True if a solution has been found, false otherwise
@post If a solution is found, the header variable will point
at itself at the end and all of the rows corresponding
to the solution will no longer be accessible from the rest
of the matrix. If no solution is found, the matrix, columns
and header will be left in their initialized state
*/
bool grid::search()
{
	// Check to see if the sudoku is solved
	if (header.right == &header)
	{
		return true;
	}
	// Choose a column to pick a row from
	column* c = findSmallest();
	coverCol(c);
	data* d = c->down;
	// Iterate through every row
	while (d != c)
	{
		output[size] = d;
		++size;
		data* r = d->right;
		// Cover every column corresponding to an element in the row
		while (r != d)
		{
			coverCol(r->col);
			r = r->right;
		}
		// Search the sudoku again for another row to pick
		if (search())
			return true;
		// Uncover every column covered in the row
		data* l = d->left;
		while (l != d)
		{
			uncoverCol(l->col);
			l = l->left;
		}
		d = d->down;
		--size;
	}
	// Uncover the column and return false as a wrong column was chosen
	uncoverCol(c);
	return false;
}

/** Covers a clue as specified by the user
@param d A pointer to the data member in the row to be covered
@post The output array contains d and the row d is in is
selected to be part of the solution
*/
void grid::coverClue(data* d)
{
	output[size] = d;
	++size;
	coverCol(d->col);
	data* r = d->right;
	while (r != d)
	{
		coverCol(r->col);
		r = r->right;
	}
}

/** Disconnects a column and every correspnding row from the matrix
@param c The column to be covered
@post The pointers that would normally point to the
elements of the rows that are part of the column
now point to the next ones over in all directions
while the elements themselves still have their same
pointers for reinput into the matrix
*/
void grid::coverCol(column* c)
{
	c->left->right = c->right;
	c->right->left = c->left;
	data* d = c->down;
	while (d != c)
	{
		data* r = d->right;
		while (r != d)
		{
			r->up->down = r->down;
			r->down->up = r->up;
			--(r->col->size);
			r = r->right;
		}
		d = d->down;
	}
}

/** Reconnects a column and every corresponding row into the matrix
@param c The column to be uncovered
@post The pointers that pointed over the corresponding
elements of the column and its rows are reconnected
with the correct pointers pointing toward them.
*/
void grid::uncoverCol(column* c)
{
	data* u = c->up;
	while (u != c)
	{
		data* l = u->left;
		while (l != u)
		{
			l->up->down = l;
			l->down->up = l;
			++(l->col->size);
			l = l->left;
		}
		u = u->up;
	}
	c->left->right = c;
	c->right->left = c;
}

/** Finds the column with the lowest number of remaining elements
@return A pointer to the column with the lowest number of elements
*/
grid::column* grid::findSmallest()
{
	column* c = nullptr;
	column* r = (column*)header.right;
	int size = MAX_ROWS + 1;
	while (r != &header)
	{
		if (r->size < size)
		{
			size = r->size;
			c = r;
		}
		r = (column*)r->right;
	}
	return c;
}

/** Initializes the data members for the matrix
@post All of the pointers in the matrix which correspond to a
completely empty sudoku matrix that would have some element
are initilized to have one. As the matrix is the same for
sudoku board before any hints are given, the locations
can be hardcoded in.
*/
void grid::initMatrix()
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		matrix[i][i / 9] = new data;
		matrix[i][i / 9]->row = i;
		matrix[i][81 + 9 * (i / 81) + i % 9] = new data;
		matrix[i][81 + 9 * (i / 81) + i % 9]->row = i;
		matrix[i][162 + i % 81] = new data;
		matrix[i][162 + i % 81]->row = i;
		matrix[i][243 + i % 9 + 9 * (i / 27) - 27 * (i / 81) + 27 * (i / 243)] = new data;
		matrix[i][243 + i % 9 + 9 * (i / 27) - 27 * (i / 81) + 27 * (i / 243)]->row = i;
	}
}

void grid::print()
{
	int outgrid[9][9];
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			outgrid[i][j] = 0;
	for (int i = 0; i < size; ++i)
	{
		int result = output[i]->row;
		int pos = result / 9;
		outgrid[pos / 9][pos % 9] = result % 9 + 1;
	}
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			std::cout << outgrid[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

/** Asks the user to input their sudoku
@post Either the user entered sudoku is entered and printed
out to the user, or a prewritten sudoku is placed instead
of a user based one.
Here is the example sudoku:
0,2,0,5,3,4,0,0,0 ,
5,0,4,0,0,0,7,0,0 ,
0,6,0,7,0,0,0,3,0 ,
2,0,7,0,4,0,0,0,8 ,
3,0,0,6,0,8,0,0,7 ,
6,0,0,0,9,0,3,0,5 ,
0,7,0,0,0,3,0,8,0 ,
0,0,3,0,0,0,9,0,2 ,
0,0,0,9,7,2,0,5,0
parseInput(2, 1, 2);
parseInput(5, 1, 4);
parseInput(3, 1, 5);
parseInput(4, 1, 6);
parseInput(5, 2, 1);
parseInput(4, 2, 3);
parseInput(7, 2, 7);
parseInput(6, 3, 2);
parseInput(7, 3, 4);
parseInput(3, 3, 8);
parseInput(2, 4, 1);
parseInput(7, 4, 3);
parseInput(4, 4, 5);
parseInput(8, 4, 9);
parseInput(3, 5, 1);
parseInput(6, 5, 4);
parseInput(8, 5, 6);
parseInput(7, 5, 9);
parseInput(6, 6, 1);
parseInput(9, 6, 5);
parseInput(3, 6, 7);
parseInput(5, 6, 9);
parseInput(7, 7, 2);
parseInput(3, 7, 6);
parseInput(8, 7, 8);
parseInput(3, 8, 3);
parseInput(9, 8, 7);
parseInput(2, 8, 9);
parseInput(9, 9, 4);
parseInput(7, 9, 5);
parseInput(2, 9, 6);
parseInput(5, 9, 8);
7,0,0,0,0,0,0,0,0 ,
0,0,4,8,0,0,0,0,0 ,
0,6,0,0,2,0,5,0,0 ,
0,9,0,0,0,5,0,0,0 ,
0,0,0,0,1,0,2,0,0 ,
0,0,0,2,0,7,0,4,0 ,
0,0,2,0,0,0,0,8,6 ,
0,0,3,1,0,0,0,7,0 ,
0,8,0,0,0,0,4,0,0
parseInput(7, 1, 1);
parseInput(4, 2, 3);
parseInput(8, 2, 4);
parseInput(6, 3, 2);
parseInput(2, 3, 5);
parseInput(5, 3, 7);
parseInput(9, 4, 2);
parseInput(5, 4, 6);
parseInput(1, 5, 5);
parseInput(2, 5, 7);
parseInput(2, 6, 4);
parseInput(7, 6, 6);
parseInput(4, 6, 8);
parseInput(2, 7, 3);
parseInput(8, 7, 8);
parseInput(6, 7, 9);
parseInput(3, 8, 3);
parseInput(1, 8, 4);
parseInput(7, 8, 8);
parseInput(8, 9, 2);
parseInput(4, 9, 7);
7,0,0,0,0,0,0,0,0 ,
0,0,4,8,0,0,0,0,0 ,
0,6,0,0,2,0,5,0,0 ,
0,9,0,0,0,5,0,0,0 ,
0,0,0,0,1,8,2,0,0 ,
0,0,0,2,0,0,0,4,0 ,
0,0,2,0,0,0,0,8,6 ,
0,0,3,1,0,0,0,7,0 ,
0,8,0,0,0,0,4,0,0
parseInput(7, 1, 1);
parseInput(4, 2, 3);
parseInput(8, 2, 4);
parseInput(6, 3, 2);
parseInput(2, 3, 5);
parseInput(5, 3, 7);
parseInput(9, 4, 2);
parseInput(5, 4, 6);
parseInput(1, 5, 5);
parseInput(8, 5, 6);
parseInput(2, 5, 7);
parseInput(2, 6, 4);
parseInput(4, 6, 8);
parseInput(2, 7, 3);
parseInput(8, 7, 8);
parseInput(6, 7, 9);
parseInput(3, 8, 3);
parseInput(1, 8, 4);
parseInput(7, 8, 8);
parseInput(8, 9, 2);
parseInput(4, 9, 7);
*/
void grid::askUser()
{
	parseInput(7, 1, 1);
	parseInput(4, 2, 3);
	parseInput(8, 2, 4);
	parseInput(6, 3, 2);
	parseInput(2, 3, 5);
	parseInput(5, 3, 7);
	parseInput(9, 4, 2);
	parseInput(5, 4, 6);
	parseInput(1, 5, 5);
	parseInput(8, 5, 6);
	parseInput(2, 5, 7);
	parseInput(2, 6, 4);
	parseInput(4, 6, 8);
	parseInput(2, 7, 3);
	parseInput(8, 7, 8);
	parseInput(6, 7, 9);
	parseInput(3, 8, 3);
	parseInput(1, 8, 4);
	parseInput(7, 8, 8);
	parseInput(8, 9, 2);
	parseInput(4, 9, 7);
		std::cout << "Prewritten sudoku chosen, here is what it looks like ::" << std::endl << std::endl;
		print();
}