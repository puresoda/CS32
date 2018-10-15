#include "History.h"

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;

	//temporarily fill storage with zeros
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
			storage[i][j] = 0;
}

History::~History()
{

}

bool History::record(int r, int c)
{
	// if position is out of bounds
	if (r > m_rows || c > m_cols || r <= 0 || c <= 0)
		return false;
	else
	{
		//following a successful convversion, add 1 to element corresponding to that position
		storage[r-1][c-1] += 1;
		return true;
	}
}

void History::display() const
{
	int r, c;
	char output;
	clearScreen();

	//display history
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
		{
			if (storage[r][c] == 0)
				output = '.';
			else if (storage[r][c] <= 26)
				//use ASCII values to convert from int to character
				output = storage[r][c] + 64;
			else
				output = 'Z';

			cout << output;
		}
		cout << endl;
	}
	cout << endl;
}