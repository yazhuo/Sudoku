#ifndef grid_h
#define grid_h


class grid
{
public:
	grid();
	~grid();
	bool search();
	void print();
private:
	// Member structs

	struct column;

	/* data struct
	Each data object contains pointers to the next initialized
	data member to the right, left, up, and down directions in
	the larger matrix.
	In addition, a pointer to the columns that the data object
	corresponds to and an integer representing the row that
	the object is in.
	*/
	struct data
	{
	public:
		data* right;
		data* left;
		data* up;
		data* down;
		column* col;
		int row;
	};

	/* column struct
	The columns class is a subclass of the data object, and
	has the same corresponding left, right, up and down pointers
	to data objects. However the left and right pointers will
	only point to column objects and the column pointer will
	point to itself.
	In addition the column pointer contains 2 integers, a size
	variable that keeps track of how many data objects are in
	its column and a name fow which column it is
	*/
	struct column : public data
	{
	public:
		int size;
		int name;
	};

	// Member functions
	
	void initMatrix();
	void parseInput(int n, int r, int c);
	void askUser();
	void coverClue(data* d);
	void coverCol(column*c);
	void uncoverCol(column* c);
	column* findSmallest();

	// Member variables
	data** output;
	data*** matrix;
	column** columns;
	column header;
	int size;

	// Member constants
	const int MAX_ROWS = 729;
	const int MAX_COLS = 324;
};

#endif /* grid_h */
