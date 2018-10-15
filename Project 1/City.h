#ifndef CITY_INCLUDED
#define CITY_INCLUDED

#include "globals.h"
#include "History.h"

class Player;
class Flatulan;

class City
{
public:
	// Constructor/destructor
	City(int nRows, int nCols);
	~City();

	// Accessors
	int rows() const;
	int cols() const;
	Player* player() const;
	int flatulanCount() const;
	int nFlatulansAt(int r, int c) const;
	bool isPlayerAt(int r, int c) const;
	bool determineNewPosition(int& r, int& c, int dir) const;
	void display() const;

	// Mutators
	bool addFlatulan(int r, int c);
	bool addPlayer(int r, int c);
	void preachToFlatulansAroundPlayer();
	void moveFlatulans();

	// History Accessor
	History& history();

private:
	int m_rows;
	int m_cols;
	Player* m_player;
	Flatulan* m_flatulans[MAXFLATULANS];
	int m_nFlatulans;
	History m_history;

	// Helper functions
	bool isInBounds(int r, int c) const;
};

#endif