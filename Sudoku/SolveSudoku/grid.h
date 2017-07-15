#ifndef GRID_H
#define GRID_H

const int MAX_COLS = 324;
const int MAX_NODES = 1 + 81 * 4 + 9 * 9 * 9 * 4;
const int kRow = 80, kCol = 161, kBox = 242;

class grid
{
public:
	grid();
	~grid();
	bool search();
	void print();
	
	
private:
	struct column;
	
	struct node
	{
		node* right;
		node* left;
		node* up;
		node* down;
		column* col;
	};

	struct column : public node
	{
		int count;
		int name;
	};

	
	void traversalValue();
	void traversalBlank();
	void coverCol(column* c);
	void uncoverCol(column* c);
	void removeCol(column* c);
	node* addRow(int col);
	int get_col_col(int c, int v);
	int get_row_col(int r, int v);
	int get_box_col(int b, int v);
	void put_up(column* c, node* r);
	void put_right(node* o, node* n);
	column* findSmallest();

	void testOutput();

	node** output_;   //´æ´¢½á¹ûÐÐ
	column** columns_;
	column header_;
	node nodes_[MAX_NODES];
	int cur_node_;
	int size;
};

#endif // !GRID_H
