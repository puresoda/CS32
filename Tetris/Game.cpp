#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
	: m_well(width, height), m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_board(height + 1, std::vector<char>(width + 2)), m_level(1), 
		m_score(0), m_left(5), m_width(width), m_height(height),m_piece(nullptr),m_nextpiece(nullptr)
{
	//fill the board
	for (size_t i = 0; i < m_board.size(); i++)
		(m_board[i]).assign(m_board[i].size(), ' ');

	//draw the sides of the well
	for (size_t i = 0; i < m_board.size(); i++)
	{
		m_board[i][0] = '@';
		m_board[i][m_board[i].size() - 1] = '@';
	}

	//draw the bottom of the well
	for (size_t i = 0; i < m_board[m_board.size() - 1].size(); i++)
		m_board[m_board.size() - 1][i] = '@';

}

Game::~Game()
{
	//delete dynamically allocated pieces
	delete m_piece;
	delete m_nextpiece;
}

void Game::play()
{
    displayStatus();  //  score, rows left, level
	m_well.display(m_screen, WELL_X, WELL_Y);
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
		if (!playOneLevel())
			break;

		m_nextpiece->print(' ');

        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
		clearBoard();

        m_level++;
		displayStatus();  //  score, rows left, level
    }

    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
   m_screen.gotoXY(PROMPT_X, PROMPT_Y);
   m_screen.printStringClearLine(s);   // overwrites previous text
   m_screen.refresh();
}

void Game::displayStatus()
{
	std::string score = "Score:     " + std::to_string(m_score);
	std::string left = "Rows Left: " + std::to_string(m_left);
	std::string level = "Level:     "  + std::to_string(m_level);
	std::string score_space = "";
	std::string left_space = "";
	std::string level_space = "";

	for (int i = score.length(); i < 17; i++)
		score_space += " ";
	for (int i = left.length(); i < 17; i++)
		left_space += " ";
	for (int i = level.length(); i < 17; i++)
		level_space += " ";

	//display score
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printStringClearLine("Score:     " + score_space + std::to_string(m_score));

	//display rows left
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printStringClearLine("Rows Left: " + left_space + std::to_string(m_left));

	//display the level
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printStringClearLine("Level:     " + level_space + std::to_string(m_level));

	m_screen.refresh();
}

bool Game::playOneLevel()
{
	//start the timer
	Timer t;
	t.start();

	//update rows left and display the status
	m_left = 5 * m_level;
	displayStatus();
	displayNextPiece();

	//create and move current piece to correct position
	addPiece(m_piece);
	m_piece->move(4, 0);

	//create new next piece
	delete m_nextpiece;
	addPiece(m_nextpiece);

	//display the pieces
	m_piece->display();
	m_nextpiece->display();

	while (m_left > 0)
	{
		char ch = '!';
		getCharIfAny(ch);

		//movement controls
		switch (ch)
		{
			case 's':
			case '2':
				m_piece->drop();
				break;
			case 'a':
			case ARROW_LEFT:
				m_piece->left();
				break;
			case 'd':
			case ARROW_RIGHT:
				m_piece->right();
				break;
			case 'w':
			case ARROW_UP:
				m_piece->rotate();
				break;
			case 'q':
				return false;
			case ' ':
				m_piece->fastdrop();
				goto placement; //skip waiting for timer to end and immediately create new piece
				break;
			default: 
				break;
		}

		if (t.elapsed() > (1000 - (100 * (m_level - 1))) || (m_level >= 9 && t.elapsed() > 100))
		{
			if (m_piece->falling())
			{
				m_piece->drop();
				m_screen.gotoXY(m_width + 2, m_height); //move cursor somewhere else
				t.start(); //restart the timer
			}

			else
			{
				placement:
				//update the board and screen
				m_piece->set();

				//temporaryily set score multiplier to zero
				int score_mult = 0;

				//clear and count all completed rows
				for (int i = 1; i < m_height; i++)
					if (cleared(m_board[i]))
						score_mult += clearRow(i);

				//apply score multiplier
				if(score_mult!= 0)
					m_score += 100 * pow(2, score_mult-1);

				//update status
				displayStatus();

				//restart timer and delete the piece
				delete m_piece;
				t.start();

				if (m_left > 0)
				{
					//make next piece our current one
					m_piece = m_nextpiece;
					if (!m_piece->move(4, 0))
						return false;
					
					//create new next piece
					addPiece(m_nextpiece);
					m_nextpiece->display();
				}
			}
		}

	}

	return true;
}

void Game::addPiece(Piece*& piece)
{
	switch (chooseRandomPieceType())
	{
	case PIECE_I:
		piece = new I_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_L:
		piece = new L_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_J:
		piece = new J_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_T:
		piece = new T_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_O:
		piece = new O_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_S:
		piece = new S_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_Z:
		piece = new Z_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_VAPOR:
		piece = new VAPOR_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_FOAM:
		piece = new FOAM_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	case PIECE_CRAZY:
		piece = new CRAZY_Piece(this,&m_screen,NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	default:
		piece = new FOAM_Piece(this, &m_screen, NEXT_PIECE_X, NEXT_PIECE_Y);
		break;
	}

}

bool Game::draw(int x, int y, char ch)
{
	//check bad input
	if (x <= 0 || x >= m_width+1 || y <= 0 || y >= m_height)
		return false;

	//update the board
	m_board[y][x] = ch;

	return true;
}

void Game::clearBoard()
{
	//write everything to blank character
	for (size_t i = 0; i < m_board.size()-1; i++)
		for(size_t j = 1; j < m_board[i].size() -1; j++)
			m_board[i][j] = ' ';

	//clear the screen
	for(size_t i =0; i < m_board.size()-1; i++)
		for (size_t j = 1; j < m_board[i].size() - 1; j++)
		{
			m_screen.gotoXY(WELL_X + j, WELL_Y + i);
			m_screen.printChar(' ');
		}
}

void Game::displayNextPiece()
{
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next Piece: ");
}

std::vector<std::vector<char>> Game::getBoard()
{
	return m_board;
}

int Game::clearRow(int y)
{
	//rows left shouldn't drop below zero
	if(m_left >= 1)
		m_left--;

	//clear the row off the screen
	for (int i = 1; i < m_width+1; i++)
	{
		m_screen.gotoXY(i, y);
		m_screen.printChar(' ');
		m_board[y][i] = ' ';
	}

	//swap the row with the ones above it
	for (int i = y; i > 0; i--)
		m_board[i].swap(m_board[i - 1]);
	
	//print to the screen based on the updated board
	for (int i = y; i > 0; i--)
		for(int j = 1; j < 11; j++)
		{ 
			m_screen.gotoXY(j, i);
			m_screen.printChar(m_board[i][j]);	
		}

	//return value is used to count how many rows are cleared simmultaneously 
	return 1;
}

bool Game::cleared(std::vector<char> row)
{
	//check if row has any empty cells
	for (size_t i = 1; i < row.size() - 1; i++)
		if (row[i] == ' ')
			return false;

	return true;
}

int Game::getX()
{
	return m_width;
}

int Game::getY()
{
	return m_height;
}