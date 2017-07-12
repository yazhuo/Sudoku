#ifndef COORD_H
#define COORD_H

//存储格子的行和列
class Coord
{
public:
	int x;
	int y;

	Coord(int xvalue = 0, int yvalue = 0)
	{
		x = xvalue;
		y = yvalue;
	}
};

#endif // !COORD_H
