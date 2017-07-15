#include "grid.h"
#include "sudoku.h"
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

grid::grid()
{
	cur_node_ = 0;
	size = 0;
	output_ = new node*[81];
	columns_ = new column*[MAX_COLS];

	// 为列首元素分配节点
	for (int i = 0; i < MAX_COLS; i++)
	{
		columns_[i] = new column;
	}

	// 连接列首元素
	for (int i = 0; i < MAX_COLS; i++)
	{
		if (i == 0)
		{
			columns_[i]->left = &header_;
			columns_[i]->right = columns_[i + 1];
		}
		else if (i == MAX_COLS - 1)
		{
			columns_[i]->left = columns_[i - 1];
			columns_[i]->right = &header_;
		}
		else
		{
			columns_[i]->left = columns_[i - 1];
			columns_[i]->right = columns_[i + 1];
		}
		columns_[i]->count = 0;
		columns_[i]->up = columns_[i];
		columns_[i]->down = columns_[i];
		columns_[i]->col = columns_[i];
		columns_[i]->name = i;
	}

	// 连接列首元素与头节点
	header_.right = columns_[0];
	header_.left = columns_[MAX_COLS - 1];

	traversalValue();
	//cout << "after traversalValue size =  " << size << endl;
	traversalBlank();
	//cout << "after traversalBlank size =  " << size << endl;
	/*for (int i = 0; i < size; i++)
	{
		cout << output_[i]->col->name << " ";
		cout << output_[i]->right->col->name << " ";
		cout << output_[i]->right->right->col->name << " ";
		cout << output_[i]->right->right->right->col->name << " ";
		cout << endl;
	}*/
}

grid::~grid()
{
	for (int i = 0; i < MAX_COLS; ++i)
		delete columns_[i];
	delete [] columns_;
	delete[] output_;
}

void grid::traversalValue()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != 0)
			{
				node* no = addRow(i * 9 + j);
				no->col->count = -1;
				node* nr = addRow(get_row_col(i, sudoku[i][j]));
				nr->col->count = -1;
				node* nc = addRow(get_col_col(j, sudoku[i][j]));
				nc->col->count = -1;
				node* nb = addRow(get_box_col(i / 3 * 3 + j / 3, sudoku[i][j]));
				nb->col->count = -1;

				if (no && nr && nc && nb)
				{
					put_right(no, nr);
					put_right(nr, nc);
					put_right(nc, nb);
					output_[size++] = no;

					//移除这些列的列首元素
					removeCol(no->col);
					removeCol(nr->col);
					removeCol(nc->col);
					removeCol(nb->col);
				}				
			}
		}
	}
}

void grid::traversalBlank()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				for (int v = 1; v < 10; v++)
				{
					node* no = addRow(i * 9 + j);
					node* nr = addRow(get_row_col(i, v));
					node* nc = addRow(get_col_col(j, v));
					node* nb = addRow(get_box_col(i / 3 * 3 + j / 3, v));

					if (no && nr && nc && nb )
					{
						put_right(no, nr);
						put_right(nr, nc);
						put_right(nc, nb);
						//output_[size++] = no;
					}
				}
			}
		}
	}
}

grid::node* grid::addRow(int col)
{
	if (columns_[col]->count == -1)
		return nullptr;

	assert(cur_node_ < MAX_NODES);
	node* r = &nodes_[cur_node_++];
	memset(r, 0, sizeof(node));

	r->left = r;
	r->right = r;
	r->up = r;
	r->down = r;
	r->col = columns_[col];
	put_up(r->col, r);
	return r;
}

int grid::get_row_col(int r, int v)
{
	return kRow + r * 9 + v;
}

int grid::get_col_col(int c, int v)
{
	return kCol + c * 9 + v;
}

int grid::get_box_col(int b, int v)
{
	return kBox + b * 9 + v;
}

void grid::put_up(column* c, node* r)
{
	r->up = c->up; /* 需要注意的是,Column结构是一个十字交叉链表 */
	r->down = c;
	c->up->down = r;
	c->up = r;
	c->count++; /* size表示这一列增加了一个元素 */
	r->col = c;
}

void grid::put_right(node* o, node* n)
{
	n->right = o->right;
	n->left = o;
	o->right->left = n;
	o->right = n;
}

void grid::removeCol(column* c)
{
	c->right->left = c->left;
	c->left->right = c->right;		
}

grid::column* grid::findSmallest()
{
	
	column* c = (column*)header_.right;
	int min_size = c->count;
	if (min_size > 1)
	{
		for (column* cc = (column*)c->right; cc != &header_; cc = (column*)cc->right)
		{
			if (min_size > cc->count)
			{
				c = cc;
				min_size = cc->count;
				if (min_size <= 1)
					break;
			}
		}
	}
	return c;
}

void grid::coverCol(column* c)
{
	c->right->left = c->left;
	c->left->right = c->right;
	for (node* i = c->down; i != c; i = i->down)
	{
		for (node* j = i->right; j != i; j = j->right)
		{
			j->down->up = j->up;
			j->up->down = j->down;
			j->col->count--;
		}
	}
}

void grid::uncoverCol(column* c)
{
	for (node* i = c->up; i != c; i = i->up)
	{
		for (node* j = i->left; j != i; j = j->left)
		{
			j->col->count++;
			j->down->up = j;
			j->up->down = j;
		}
	}
	c->right->left = c;
	c->left->right = c;
}


bool grid::search()
{
	if (header_.right == &header_)
	{
		return true;
	}

	//column* col = findSmallest();
	column* col = (column*)header_.right;
	coverCol(col);
	for (node* row = col->down; row != col; row = row->down)
	{
		output_[size++] = row;
		//testOutput();
		for (node* j = row->right; j != row; j = j->right) 
		{
			coverCol(j->col);
		}
		if (search())
			return true;
		--size;
		for (node* j = row->left; j != row; j = j->left) {
			uncoverCol(j->col);
		}
	}
	uncoverCol(col);
	return false;
}

void grid::print()
{
	int outgrid[9][9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			outgrid[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		node* row = output_[i];
		int pos = row->col->name;
		int val = (row->right->col->name - kRow - 1) % 9 + 1;
		//int pos = -1;
		//int val = -1;
		//while (pos == -1 || val == -1)
		//{
		//	if (row->col->name < 81)
		//	{
		//		pos = row->col->name;
		//	}
		//	if(row->col->name > 80 && row->col->name < 162)
		//	{
		//		val = (row->col->name - kRow - 1) % 9 + 1;
		//	}
		//}
		//row = row->right;
		outgrid[pos / 9][pos % 9] = val;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << outgrid[i][j] << " ";
		}
		cout << endl;
	}
}

void grid::testOutput()
{
	for (int i = 0; i < size; i++)
	{
		cout << output_[i]->col->name << " ";
		cout << output_[i]->right->col->name << " ";
		cout << output_[i]->right->right->col->name << " ";
		cout << output_[i]->right->right->right->col->name << " ";
		cout << endl;
	}
	cout << endl;
}