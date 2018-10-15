#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <vector>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
	~Game();

    void play();
	bool playOneLevel();

	//display functions
    void displayPrompt(std::string s);
    void displayStatus();
	void displayNextPiece();
	void clearBoard();

	//dynamically generate a new piece
	void addPiece(Piece*& piece);
	
	//update the board
	bool draw(int x, int y, char ch);

	//clear rows
	int clearRow(int y);
	bool cleared(std::vector<char> row);

	//get funcions
	std::vector<std::vector<char>> getBoard();
	int getX();
	int getY();

  private:
    Well m_well;
    Screen m_screen;
	std::vector<std::vector<char>> m_board;

	Piece* m_piece;
	Piece* m_nextpiece;

    int m_level;
	int m_score;
	int m_left;
	int m_width;
	int m_height;
};

#endif // GAME_INCLUDED
