#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
	//Constructor and Destructor
	History(int nRows, int nCols);
	~History();

	//Mutators
	bool record(int r, int c);

	//Accessors
	void display() const;

private:
	int m_rows;
	int m_cols;
	int storage[MAXROWS][MAXCOLS]; //store the location of successful conversions
};

#endif