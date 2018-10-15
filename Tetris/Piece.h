#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include <vector>

enum PieceType 
{
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

class Screen;
class Game;

class Piece
{
public:
	//Constructor
	Piece(Game* game, Screen* screen, int type, int x, int y);
	virtual ~Piece();

	//display functions
	void print(char ch);
	void display();

	//movement functions
	bool move(int x, int y);

	void rotate();
	virtual bool canrotate() const = 0;

	void drop();
	void fastdrop();

	virtual void right();
	virtual void left();

	virtual void set();

	//Getter functions
	int getOrientation() const;
	bool falling() const;
	int getY() const;
	int getX() const;

private:
	int m_orientation;
	int m_type;
	int m_x;
	int m_y;
	bool m_falling;

	std::vector<std::vector<int>> m_output;

//derived classes need access to the screen and game in order to utilize the board and print to the screen
protected:
	Screen* m_screen;
	Game* m_game;
};

class T_Piece :public Piece
{
public:
	T_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 0, x, y) {};
	bool canrotate() const;
};

class L_Piece :public Piece
{
public:
	L_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 1, x, y) {};
	bool canrotate() const;
};

class J_Piece :public Piece
{
public:
	J_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 2, x, y) {};
	bool canrotate() const;
};

class O_Piece :public Piece
{
public:
	O_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 3, x, y) {};
	bool canrotate() const;
};

class S_Piece :public Piece
{
public:
	S_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 4, x, y) {};
	bool canrotate() const;
};

class Z_Piece :public Piece
{
public:
	Z_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 5, x, y) {};
	bool canrotate() const;
};

class I_Piece :public Piece
{
public:
	I_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 6, x, y) {};
	bool canrotate() const;
};

class VAPOR_Piece :public Piece
{
public:
	VAPOR_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 7, x, y) {};
	void set();
	bool canrotate() const;
};

class FOAM_Piece :public Piece
{
public:
	FOAM_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 8, x, y) {};
	void set();
	bool canrotate() const;
	bool foam(int x, int y);
};

class CRAZY_Piece :public Piece
{
public:
	CRAZY_Piece(Game* game, Screen* screen, int x, int y) :Piece(game, screen, 9, x, y) {};
	void left();
	void right();
	bool canrotate() const;
};

//chooseRandomPieceType() is implemented in chetryris.cpp
PieceType chooseRandomPieceType();

#endif // Piece_INCLUDED
