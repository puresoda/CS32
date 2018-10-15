#include "Piece.h"
#include "Game.h"
#include "UserInterface.h"
#include <algorithm>

const std::vector<std::vector<std::vector<int>>> T_PERM = 
{
	{{0, 1, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},

	{{0,0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},
};

const std::vector<std::vector<std::vector<int>>> L_PERM = 
{
	{{0, 0, 0, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}},

	{{0,0, 0, 0},
	{0, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0}},
};

const std::vector<std::vector<std::vector<int>>> J_PERM = 
{
	{{0, 0, 0, 0},
	{0, 1, 1, 1},
	{0, 0, 0, 1},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 1, 1, 0}},

	{{0,0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 1},
	{0, 0, 0, 0}},

	{{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},
};

const std::vector<std::vector<std::vector<int>>> O_PERM = 
{
	{{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}}
};

const std::vector<std::vector<std::vector<int>>> S_PERM = 
{
	{{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}}
};

const std::vector<std::vector<std::vector<int>>> Z_PERM = 
{
	{{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0}},

	{{0, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0}},

	{{0, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}}
};

const std::vector<std::vector<std::vector<int>>> I_PERM = 
{
	{{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0}},

	{{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0}}
};

const std::vector<std::vector<std::vector<int>>> VAPOR_PERM = 
{
	{{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},
	
	{{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},
	
	{{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

};

const std::vector<std::vector<std::vector<int>>> FOAM_PERM = 
{
	{{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},
};

const std::vector<std::vector<std::vector<int>>> CRAZY_PERM = 
{
	{{1, 0, 0, 1},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}},

	{{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}},

	{{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 0, 0, 1}},

	{{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 0, 0, 0}}
};

const std::vector<std::vector<std::vector<int>>> ALL_PERM[10] = 
	{ T_PERM, L_PERM, J_PERM, O_PERM, S_PERM, Z_PERM, I_PERM, VAPOR_PERM, FOAM_PERM, CRAZY_PERM };

Piece::Piece(Game* game, Screen* screen, int type, int x, int y)
	:m_orientation(0), m_type(type), m_x(x), m_y(y), m_falling(true), m_output(ALL_PERM[m_type][m_orientation]), m_screen(screen), m_game(game)
{

}

Piece::~Piece()
{

}

void Piece::set()
{
	//update the board
	for (size_t i = 0; i < m_output.size(); i++)
		for (size_t j = 0; j < m_output[i].size(); j++)
			if (m_output[i][j] != 0)
				m_game->draw(m_x + j, m_y + i, '$');

	//update the screen
	print('$');
}

void Piece::print(char ch)
{
	//update the screen with the piece
	for (size_t i = 0; i < m_output.size(); i++)
	{
		for (size_t j = 0; j < m_output[i].size(); j++)
			if (m_output[i][j] != 0)
			{
				m_screen->gotoXY(m_x + j, m_y + i);
				m_screen->printChar(ch);
			}
	}
}

void Piece::display()
{
	this->print('#');
}

void Piece::rotate()
{
	//can only rotate if the piece has not been placed
	if (!m_falling)
		return;

	if (!canrotate())
		return;

	int temp = m_orientation;

	//update orientation
	if (m_orientation < 3)
		temp++;
	else
		temp = 0;

	//check for any rotation conflicts
	for (size_t i = 0; i < unsigned(std::min(4, m_game->getY() - m_y)); i++)
		for (size_t j = 0; j < unsigned(std::min(4, m_game->getX() - m_x + 1)); j++)
			if ((ALL_PERM[m_type][temp][i][j] == 1) && (m_game->getBoard()[m_y + i][m_x + j] != ' '))
				return;

	m_orientation = temp;

	//take old orientation off the screen
	this->print(' ');

	//update the output
	m_output = ALL_PERM[m_type][m_orientation];

	//update the screen with new orientation
	this->display();
}

void Piece::drop()
{
	if (!m_falling)
		return;

	int temp = m_x;

	//absolute value in the event that x is less than 0
	if (m_x < 0)
		temp = -1 * m_x;

	//check for possible collisions
	for (size_t i = 0; i < unsigned(std::min(4,m_game->getY()-m_y)); i++)
		for (size_t j = 0; j < unsigned(std::min(4,m_game->getX()+1-m_x)); j++)
			if ((m_game->getBoard()[m_y + 1 + i][temp + j] != ' ') && (m_output[i][j] == 1))
			{
				//piece has stopped moving
				m_falling = false;
				return;
			}

	//update the board and screen
	this->print(' ');
	m_y++;
	this->display();
}

void Piece::fastdrop()
{
	bool candrop = true;
	int dropcount;

	//count how many times the piece can drop
	for (dropcount = 0; candrop; dropcount++)
	{
		for (size_t i = 0; i < unsigned(std::min(4, m_game->getY() - m_y)); i++)
			for (size_t j = 0; j < unsigned(std::min(4, m_game->getX() - m_x+1)); j++)
				if ((m_output[i][j] == 1) && (m_game->getBoard()[m_y + dropcount + i][m_x + j] != ' '))
					candrop = false;
	}

	//move the piece to correct position
	if(dropcount > 4)
		this->move(m_x, m_y + dropcount-4);

	//just in case the piece is not at the bottom yet
	this->drop();
	this->drop();

	m_falling = false;
}

void Piece::left()
{
	if (!m_falling)
		return;

	//collision check
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if (m_output[i][j] == 1 && m_game->getBoard()[m_y + i][m_x + j - 1] != ' ')
				return;

	//update screen
	this->print(' ');
	m_x--;
	this->display();
}

void Piece::right()
{
	if (!m_falling)
		return;

	//prevent out of bounds vector access
	if (m_x >= m_game->getX() -3)
		for (int i = 0; i < 4; i++)
			if (m_output[i][10 - m_x] == 1)
				return;
	
	//check for collision
	for(int j = 3; j >= 0; j--)
		for (int i = 0; i < 4; i++)
			if (m_output[i][j] == 1 && m_game->getBoard()[m_y+i][m_x + j + 1] != ' ')
				return;

	//update the screen
	this->print(' ');
	m_x++;
	this->display();
}

bool Piece::move(int x, int y)
{
	//collision check
	for (int i = 0; i < 4 && x + i <= m_game->getX(); i++)
		for (int j = 0; j < 4 && y + j < m_game->getY(); j++)
			if (m_game->getBoard()[j + y][i + x] != ' ' && m_output[j][i] == 1)
				return false;
	
	this->print(' ');

	//update the screen
	m_x = x;
	m_y = y;
	this->display();
	return true;
}

bool Piece::falling() const
{
	return m_falling;
}

int Piece::getY() const
{
	return m_y;
}

int Piece::getX() const
{
	return m_x;
}

int Piece::getOrientation() const
{
	return m_orientation;
}

void CRAZY_Piece::left()
{
	Piece::right();
}

void CRAZY_Piece::right()
{
	Piece::left();
}

void VAPOR_Piece::set()
{
	Piece::print(' ');

	//delete the four pieces above and below while checking for out of bounds access
	for(int i = 1; getX() + i <= m_game->getX() && i < 3; i++)
		for (int j = -2; getY() + j > 0 && getY() + j < m_game->getY() && j < 3; j++)
		{
			m_screen->gotoXY(getX() + i, getY() + j);
			m_screen->printChar(' ');
			m_game->draw(getX() + i, getY() + j, ' ');
		}
}

void FOAM_Piece::set()
{
	Piece::print('*');
	foam(getX() + 1, getY() + 1);
}

bool FOAM_Piece::foam(int x, int y)
{
	//set the bounds of the foam
	if (x > m_game->getX() || x <= 0 || y >= m_game->getY() || y <= 0 || y < getY() -1 || y > getY() + 3 || x < getX() -1 || x > getX() +3 )
			return false;

	//update the screen and board
	m_game->draw(x, y, '*');
	m_screen->gotoXY(x, y);
	m_screen->printChar('*');

	for (int i = y - 1; i <y + 2; i++)
		for (int j = x - 1; j < x + 2; j++) //scan through the 8 adjacent tiles
			if (abs(y - i + x - j) == 1 && j <= m_game->getX() && i < m_game->getY()) // only check the 4 orthogonal tiles
				if (m_game->getBoard()[i][j] == ' ')  //if able to move orthogonally
					if (foam(j, i)) //recursive call
						return true;


	return false;
}

bool T_Piece::canrotate() const
{
	if (getOrientation() == 1 && getX() == 0)
		return false;
	else if (getOrientation() == 0 && getY() == m_game->getY() - 2)
		return false;
	else if (getOrientation() == 3 && getX() == m_game->getX()-1)
		return false;

	return true;
}

bool L_Piece::canrotate() const 
{
	if (getOrientation() == 1 && getX() == 0)
		return false;
	else if (getOrientation() == 2 && getY() == m_game->getY() - 3)
		return false;
	else if (getOrientation() == 3 && getX() == 0)
		return false;

	return true;
}

bool J_Piece::canrotate() const
{
	if (getOrientation() == 0 && getY() == m_game->getY() - 3)
		return false;
	else if (getOrientation() == 1 && getX() == m_game->getX() - 1)
		return false;

	return true;
}

bool S_Piece::canrotate() const
{
	if (getOrientation() % 2 != 0 && getX() == 0)
		return false;

	return true;
}

bool Z_Piece::canrotate() const
{
	if (getOrientation() % 2 != 0 && getX() == 0)
		return false;

	return true;
}

bool I_Piece::canrotate() const
{
	if (getOrientation() % 2 == 0 && getY() == m_game->getY() - 2)
		return false;
	else if (getOrientation() % 2 != 0 && (getX() == 0 || getX() >= m_game->getX() - 2))
		return false;

	return true;
}

bool CRAZY_Piece::canrotate() const
{
	if (getOrientation() == 0 && getY() >= m_game->getY() - 3)
		return false;
	else if (getOrientation() == 1 && getX() <= 0)
		return false;
	else if (getOrientation() == 3 && getX() >= m_game->getX() - 2)
		return false;

	return true;
}

bool O_Piece::canrotate() const
{
	return false;
}

bool VAPOR_Piece::canrotate() const
{
	return false;
}

bool FOAM_Piece::canrotate() const
{
	return false;
}
